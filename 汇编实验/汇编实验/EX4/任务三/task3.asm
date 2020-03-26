.386
DATA SEGMENT USE16
NUMBER DB 09H,08H,07H,04H,02H,00H
DATA ENDS
STACK SEGMENT USE16	STACK
	DB 200 DUP(0)
STACK ENDS
CODE SEGMENT USE16
	ASSUME CS:CODE,SS:STACK,DS:DATA

START:
	MOV AX,DATA
	MOV DS,AX
	MOV CX,6
	MOV DI,OFFSET NUMBER
BEGIN:
	PUSH CX
	MOV AL,[DI]
	OUT 70H,AL
	IN AL,71H;读取数据
	MOV AH,AL
	AND AL,0FH
	SHR AH,4
	MOV BX,AX
	;MOV AH,0
	;MOV AL,BH
	;MOV CX,10
	;MUL CL
	;ADD AL,BL
	;MOV AH,0
	;MOV CL,16
	;DIV CL
	;MOV BH,AL
	;MOV BL,AH
	ADD BX,3030H
	CMP BH,3AH
	JAE OVERFLOW1
NEXT:
	CMP BL,3AH
	JAE OVERFLOW2
	
PRINT:
	MOV DL,BH
	MOV AH,2
	INT 21H
	MOV DL,BL
	MOV AH,2
	INT 21H
	;MOV DL,'H'
	;MOV AH,2
	;INT 21H
	MOV DL,' '
	MOV AH,2
	INT 21H
	;MOV DL,0DH
	;MOV AH,2
	;INT 21H
	;MOV DL,0AH
	;MOV AH,2
	;INT 21H
	INC DI
	POP CX
	LOOP BEGIN
	
LAST:
	MOV AH,4CH
	INT 21H

OVERFLOW1:
	ADD BL,7
	JMP NEXT
	
OVERFLOW2:
	ADD BL,7
	JMP PRINT
	
CODE ENDS
END	START