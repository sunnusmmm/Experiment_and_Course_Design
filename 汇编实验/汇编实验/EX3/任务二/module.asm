PUBLIC DTOC, MODIFY_INFO, RECCOMEND_CAL, SORT
EXTRN _GA1:BYTE

.386
DATA SEGMENT USE16 PARA PUBLIC 'DATA1'

N EQU 10
DISCOUNT  DB  0AH, 0DH, 'DISCOUNT:', '$', 0, 0, 0, 0, 0, 0
PURCHASE_PRICE  DB  0AH, 0DH, 'PURCHASE_PRICE:', '$'
SALES_PRICE  DB  0AH, 0DH, 'SALES_PRICE:', '$', 0, 0, 0
PURCHASE_COUNT  DB  0AH, 0DH, 'PURCHASE_COUNT:', '$'
INVALID_INPUT  DB  0AH, 0DH, 'INVALID_INPUT', 0AH, 0DH, '$'
IN_NUM  DB  6, ?, 6 DUP(?)
TRANS_NUM  DW ?
CALCULATED DB 'CALCULATE SUCCESSFULLY!$'
DEBUG   DB  0AH, 0DH, 'DEBUG', 0AH, 0DH, '$'

DATA ENDS

STACK1 SEGMENT USE16 PARA STACK 'STACK'
    DB 200 DUP(0)
STACK1 ENDS

WRITE MACRO A
	LEA DX, A
	MOV AH, 9
	INT 21H
ENDM

_TEXT SEGMENT USE16 PARA PUBLIC 'CODE'
    ASSUME CS:_TEXT, DS:DATA, SS:STACK1
DTOC PROC               ;将数字转换为字符串输出
	PUSH DX
	PUSH CX
	PUSH SI
	PUSH BX
	MOV BX,0	
	
DTOC0:
	MOV CX,10D	
	MOV DX,0
	DIV CX		
	MOV CX,AX	
	JCXZ DTOC1	
	ADD DX,30H	
	PUSH DX
	INC BX
	JMP DTOC0
	
DTOC1:			
	ADD  DX,30H
	PUSH DX
	INC  BX		
	MOV  CX,BX 
	
DTOC2:			
	POP AX
	MOV DL,AL
	MOV AH,2
	INT 21H
	LOOP DTOC2
	
DTOC3:
	POP BX
	POP SI
	POP CX
	POP DX
	MOV AH,2       
	MOV DL,32
	INT 21H
	ret
DTOC ENDP	
	
MODIFY_INFO PROC                        ; 功能2 bx为商品地址参数
        add bx, 10
        mov di, OFFSET DISCOUNT
INPUT_DISCOUNT:
        mov dx, di
        mov ah, 9
        int 21H
        mov ax, 0
        mov al, [bx]
        call DTOC
        mov dl, '>'
        mov AH, 2               ;打印'>'
        int 21H
        lea dx, IN_NUM          ;输入数字
        mov ah, 10
        int 21H
        cmp IN_NUM[2], 0DH
        je SKIP_DISCOUNT
        call TRANSFORM
        cmp ax, 1
        je MODIFY_DISCOUNT
        lea dx, INVALID_INPUT
        mov ah, 9
        int 21H
        jmp INPUT_DISCOUNT
MODIFY_DISCOUNT:
        mov al, BYTE PTR TRANS_NUM
        mov [bx], al
SKIP_DISCOUNT:
        add di, 18
        add bx, 1
        mov cx, 3
MODIFY:
        mov dx, di
        mov ah, 9
        int 21H
        mov ax, [bx]
        call DTOC
        mov dl, '>'
        mov AH, 2               ;打印'>'
        int 21H
        lea dx, IN_NUM          ;输入数字
        mov ah, 10
        int 21H
        cmp IN_NUM[2], 0DH
        je SKIP_OTHER
        call TRANSFORM
        cmp ax, 1
        je MODIFY_OTHER
        lea dx, INVALID_INPUT
        mov ah, 9
        int 21H
        jmp MODIFY
MODIFY_OTHER:
        mov ax, TRANS_NUM
        mov [bx], ax
SKIP_OTHER:
        add di, 18
        add bx, 2
        loop MODIFY
        ret
MODIFY_INFO ENDP
	
TRANSFORM PROC
        push dx
        push cx
        push si
        xor ch, ch
        mov cl, IN_NUM[1]
        xor dx, dx 
        mov si, 0
lop:
        push cx
        mov  ax, dx
        mov  cl, 3
        ;使用乘法麻烦，左移3位+左移1位
        shl  dx, cl
        shl  ax, 1
        add  dx, ax
        xor  ah, ah
        mov  al, IN_NUM[2+si]
        cmp  al, '0'
        jb   NOT_NUM
        cmp  al, '9'
        ja   NOT_NUM
        inc  si
        sub  al, '0'
        add  dx, ax  ;dx=dx*10+ax
        pop  cx
        loop lop
        mov  TRANS_NUM, dx
        mov ax, 1
TRANSFORM_FINISH:
        pop si
        pop cx
        pop dx
        ret
NOT_NUM:
        mov ax, 0
        pop cx
        jmp TRANSFORM_FINISH
TRANSFORM ENDP

SORT PROC NEAR      ;要求近调用，栈顶N个字为商品地址
        push bp
        mov bp, sp
        add bp, 4
        push bx
        push cx
        push di
        push si
        mov si, 2
        
SORT_CONDITION:
        cmp si, N * 2
        jae SORT_FINISH
;SORT_LOOP:
        mov cx, si
INSERT_CONDITION:
        cmp si, 0
        jbe INSERT_FINISH
        mov bx, -2[bp+si]
        mov bx, 19[bx]
        mov di, [bp+si]
        cmp bx, 19[di]
        ja INSERT_FINISH
;INSERT_LOOP:
        mov bx, -2[bp+si]
        mov [bp+si], bx
        mov -2[bp+si], di
        sub si, 2
        jmp INSERT_CONDITION
INSERT_FINISH:
        mov si, cx
        add si, 2
        jmp SORT_CONDITION
SORT_FINISH:
        pop si
        pop di
        pop cx
        pop bx
        pop bp
        ret
SORT ENDP

RECCOMEND_CAL PROC NEAR		        ;计算推荐度
        push di
        push cx
        push ebx
        push eax
        push edx
        push esi
        push ds
        mov di, OFFSET _GA1
        mov cx, N
CAL_REC:
        movzx ebx, WORD PTR 11[di]      ;进货价
        imul ebx, 1280
        movzx eax, WORD PTR 13[di]
        cmp BYTE PTR 10[di], 0
        je FREE_GOOD
        cmp WORD PTR 13[di], 0
        je FREE_GOOD

        mov edx, 0
        mul BYTE PTR 10[di]
        sal edx, 16
        mov dx, ax                      ;销售价*折扣
        mov esi, edx
        mov edx, 0
        mov eax, ebx
        DIV esi
P2:
        push eax
        mov edx, 0 
        movzx eax, WORD PTR 17[di]      ;出售数量
        sal eax, 7
        movzx esi, WORD PTR 15[di]      ;进货数量

        DIV esi
        pop esi
        add eax, esi
        mov 19[di], ax
        add di, 21
        loop CAL_REC

        LEA DX,CALCULATED
        MOV AH,9
        INT 21H
        MOV DX,0AH
        MOV AH,2
        INT 21H
        pop ds
        pop esi
        pop edx
        pop eax
        pop ebx
        pop cx
        pop di
	ret
FREE_GOOD:
        mov eax, 0
        jmp P2
RECCOMEND_CAL ENDP

_TEXT ENDS
    END