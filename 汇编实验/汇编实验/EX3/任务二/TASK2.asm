EXTRN DTOC: NEAR, MODIFY_INFO: NEAR, RECCOMEND_CAL: NEAR, SORT: NEAR, _AUTH:BYTE
PUBLIC N, _GA1, _function, _foo2, _INVAL, _SORTED,_GA2,_GA3

.386 
DATA SEGMENT USE16 PARA PUBLIC 'DATA1'

N EQU 10
_GA1 DB 'PEN',7 DUP(0) ,10;商品名称及折扣
DW 35,56,100,0,? ;推荐度还未计算 
_GA2 DB 'BOOK',6 DUP(0),9 ; 商品名称及折扣
DW 12,30,180,5,? ;推荐度还未计算
_GA3 DB 'APPLE',5 DUP(0),8 ; 商品名称及折扣
DW 2,4,40,25,? ;推荐度还未计算
GA5 DB 'CARD',6 DUP(0),10 ; 商品名称及折扣
DW 1,0,40,30,? ;推荐度还未计算
GA6 DB 'CLOTHS',4 DUP(0),6 ; 商品名称及折扣
DW 35,60,24,18,? ;推荐度还未计算
GA7 DB 'RUBBER',4 DUP(0),6 ; 商品名称及折扣
DW 3,4,10,9,? ;推荐度还未计算
GAN  DB N-7 DUP('Temp-Value',8,15,0,20,0,30,0,2,0,?,?)
GA4 DB 'SHOES',5 DUP(0),7 ; 商品名称及折扣
DW 16,25,500,0,? ;推荐度还未计算
_SORTED DW N DUP(?)

INPUTGOODSNAME    DB 'PLEASE INPUT THE GOODS NAME:$'
NOTHAVEGOODS      DB 'THE GOODS DOES NOT EXITS! TRYAGAIN!$'
RANK DW 0
IN_GOODS DB 10
	     DB ?
	     DB 10 DUP(0)
_INVAL  DW  0
CRLF    DB  0DH,0AH,'$'
DEBUG   DB  0AH, 0DH, 'DEBUG', 0AH, 0DH, '$'
DATA ENDS

STACK1 SEGMENT USE16 PARA STACK 'STACK'
	DB 100 DUP(0)
STACK1 ENDS

WRITE MACRO A
	LEA DX, A
	MOV AH, 9
	INT 21H
ENDM

_TEXT SEGMENT USE16 PARA PUBLIC 'CODE'
		ASSUME CS:_TEXT, DS:DATA ,SS:STACK1

_foo2 PROC NEAR
	push ax
	push dx
	mov dl, 0AH
	mov AH, 2
	int 21H
	pop dx
	pop ax
	ret
_foo2 ENDP

_function PROC NEAR
	push ds
	push ax
    push bx
	push cx
	push dx
	push si
	push di
	MOV AX,DATA 
    MOV DS,AX

Boss:
	MOV AX, _INVAL
	CMP AX, 1
	JZ A
	CMP AX, 2
	JZ B
	CMP AX, 3
	JZ C3
	CMP AX, 4
	JZ D
	CMP AX, 5
	JZ E
	JMP COMPLETE
	
A:
	CALL FINDGOODS
	CALL PRINT
	JMP COMPLETE
	
B:
	CALL FINDGOODS
	MOV BX,DI
	CALL MODIFY_INFO
	JMP COMPLETE
	
C3:
	; WRITE _GA1
	CALL RECCOMEND_CAL
	JMP COMPLETE
	
D:
	MOV DI,OFFSET _GA1
	MOV CX,N
DO:
	PUSH DI
	ADD DI,21
	LOOP DO
	CALL SORT
	
	MOV SI,OFFSET _SORTED
	MOV CX,N
P:
	POP WORD PTR [SI]
	ADD SI,2
	LOOP P
	JMP COMPLETE
	
E:
	MOV CX,N
	MOV AX,1
	MOV BX,0
	MOV SI,OFFSET _SORTED
Q:
	PUSH AX
	MOV DI,[SI]
	ADD SI,2
	MOV DX,[DI+19]
	CMP BX,DX
	MOV BX,DX
	JZ K
	MOV RANK,AX
	jmp ZZZ
K:
	MOV AX,WORD PTR RANK
ZZZ:
	CALL DTOC
	CALL PRINT
	POP AX
	INC AX
	LOOP Q

COMPLETE:
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
	pop ds
	ret

_function ENDP

PRINT PROC ;传入找到商品的首地址DI
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI
	PUSH DI
	
	MOV CX,2
PRINT1:
	MOV CX,2
	MOV DL,[DI]
	CMP DL,0H
	JZ  ALLIMFOR
	MOV AH,2
	INT 21H
	INC DI
	LOOP PRINT1 

ALLIMFOR:
	POP DI
	PUSH DI
	MOV AH,2
	MOV DL,32
	INT 21H
	MOV AX,0
	MOV AL,[DI+10]
	CALL DTOC
	MOV CX,5
	ADD DI,11
MORE:
	MOV AX,[DI]
	CALL DTOC
	ADD DI,2
	LOOP MORE
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	
	POP DI
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET
	
PRINT ENDP
	
FINDGOODS PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	PUSH SI

GOODSINPUT: 
	LEA DX,INPUTGOODSNAME
	MOV AH,9
	INT 21H
	LEA DX,IN_GOODS
	MOV AH,10
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H	
	  
	MOV SI,OFFSET IN_GOODS
	MOV DI,OFFSET _GA1
	PUSH DI
	MOV BX,N
		
DEFCX:		
	MOV CX,[SI+1]
	MOV CH,0
	CMP CX,0
	; JZ TASK3
	MOV DX,DI
						
CHECKGOODS: ;检验商品是否存在
	MOV AH,[SI+2]
	MOV AL,[DI]
	CMP AH,AL
	JNZ DIF
	INC SI
	INC DI
	LOOP CHECKGOODS
	JMP FINAL 
		
DIF:	
	POP DI
	ADD DI,21
	PUSH DI
	MOV SI,OFFSET IN_GOODS
	DEC BX
	CMP BX,0
	JZ  RESET
	JMP DEFCX
		
RESET:  
	LEA DX,NOTHAVEGOODS
	MOV AH,9
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP GOODSINPUT
		
FINAL:	
	MOV AL,[DI]
	CMP AL,0
	JZ  O
	JMP DIF

O:
	POP DI
	
	POP SI
	POP DX
	POP CX
	POP BX
	POP AX
	RET
FINDGOODS ENDP

_TEXT ENDS
END