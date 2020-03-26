PUBLIC  _login, _IN_NAME, _IN_PWD, _AUTH, _foo

.386
STACK1 SEGMENT USE16 STACK
    DB 200 DUP(0)
STACK1 ENDS

DATA SEGMENT USE16 PARA PUBLIC 'DATA1'

INAME   DB  0AH, 0DH, 'INPUT USERNAME:', 0AH, 0DH, '$'
IPASS   DB  0AH, 0DH, 'INPUT PASSWORD:', 0AH, 0DH, '$'
LGFAIL  DB  0AH, 0DH, 'LOGIN FAILED', 0AH, 0DH, '$'
LGSUCC  DB  0AH, 0DH, 'LOGIN SUCCESS', 0AH, 0DH, '$'
_IN_NAME DB  12 DUP(0)
_IN_PWD  DB  10 DUP(0)
_AUTH   DB  0
BNAME   DB  'lay', 0, 0      ;老板姓名（必须是自己名字的拼音）
BPASS   DB  '123', 0, 0          ;密码
N       EQU  10                  ;商品总数
DEBUG   DB  0AH, 0DH, 'DEBUG', 0AH, 0DH, '$' 

DATA ENDS

WRITE MACRO A
	LEA DX, A
	MOV AH, 9
	INT 21H
ENDM

_TEXT SEGMENT USE16 PARA PUBLIC 'CODE'
	ASSUME CS:_TEXT,DS:DATA,SS:STACK1

_foo PROC FAR
        ; push ax
        ; mov ax, DATA
        ; mov ds, ax
        mov ax, 0
        ; pop ax
        retf
_foo ENDP

_login PROC NEAR
        push ds
        push bx
        push dx
        push si
        push di
        mov ax, DATA
        mov ds, ax
START_LOGIN:
        mov bx, OFFSET _IN_NAME
        cmp BYTE PTR [bx], 0DH
        jne IS_QUIT
        mov BYTE PTR _AUTH, 0                    ;游客身份进入
        jmp LOGIN_FINISH
IS_QUIT:
        cmp BYTE PTR [bx], 'q'
        jnz INPUT_PWD
        cmp BYTE PTR [bx+1], 0DH
        mov BYTE PTR _AUTH, 'q'
        jmp LOGIN_FINISH                ;输入q退出
        
INPUT_PWD:
        mov si, OFFSET BNAME
CK_NAME:
        call CMP_STRING
        cmp ax, 1
        jne CK_FAIL

        mov bx, OFFSET _IN_PWD
        mov si, OFFSET BPASS
CK_PASS:
        call CMP_STRING
        cmp ax, 1
        jne CK_FAIL
        WRITE LGSUCC
        mov BYTE PTR _AUTH, 1
        mov ax, 1
        jmp LOGIN_FINISH
CK_FAIL:
        WRITE LGFAIL
        mov ax, 0

LOGIN_FINISH:
        pop di
        pop si
        pop dx
        pop bx
        pop ds
        ret
_login ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;
CMP_STRING PROC                             ;bx字符串一(含回车)地址，si串二地址，ax返回值
        push cx
        push dx
CMP_STRING_LOOP:
        mov cx, 0
        mov dh, [bx]
        mov dl, [si]
        cmp dh, dl
        jne NOT_EQ
        inc bx
        inc si
        mov cl, [bx]
        cmp cl, 0DH
        je ISEND
        inc cl
        loop CMP_STRING_LOOP
ISEND:
        mov dl, [si]
        cmp dl, 0DH
        je IS_EQ
        cmp dl, 0
        jne NOT_EQ
IS_EQ:
        mov ax, 1
        jmp CMP_FINISH
NOT_EQ:
        mov ax, 0
CMP_FINISH:
        pop dx
        pop cx
        ret
CMP_STRING ENDP

_TEXT ENDS
END