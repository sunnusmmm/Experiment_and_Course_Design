.386 
DATA SEGMENT USE16
BNAME DB 'Niehongyong',0,0 ;老板姓名（必须是自己名字的拼音） 
BPASS DB '123456';密码 
N EQU 30 
S1 DB 'SHOP',0,10;网店名称，用0结束 
GA1 DB 'PEN',7 DUP(0) ,10;商品名称及折扣
DW 35,56,70,25,? ;推荐度还未计算 
GA2 DB 'BOOK',6 DUP(0),9 ; 商品名称及折扣
DW 12,30,25,5,? ;推荐度还未计算
GA3 DB 'APPLE',5 DUP(0),8 ; 商品名称及折扣
DW 2,4,40,25,? ;推荐度还未计算
GA4 DB 'SHOES',5 DUP(0),7 ; 商品名称及折扣
DW 16,25,16,14,? ;推荐度还未计算
GA5 DB 'CARD',6 DUP(0),10 ; 商品名称及折扣
DW 1,0,40,30,? ;推荐度还未计算
GA6 DB 'CLOTHS',4 DUP(0),6 ; 商品名称及折扣
DW 35,60,24,18,? ;推荐度还未计算
GA7 DB 'RUBBER',4 DUP(0),6 ; 商品名称及折扣
DW 3,4,10,9,? ;推荐度还未计算
GAN  DB N-7 DUP('Temp-Value',8,15,0,20,0,30,0,2,0,?,?)

AUTH DB 0 
DB ?
DB ?

INPUTBOSSNAME     DB 'PLEASE INPUT THE BOSS NAME:$'
INPUTPASSWORD     DB 'PLEASE INPUT THE PASSWORD:$'
INPUTGOODSNAME    DB 'PLEASE INPUT THE GOODS NAME:$'
FAIL              DB 'LOGININ FAILED! TRYAGAIN!$'
SUCCESS           DB 'LOGININ SUCCESSFULLY!$'
NOTHAVEGOODS      DB 'THE GOODS DOES NOT EXITS! TRYAGAIN!$'
NODISCOUNT        DB '10 $'

IN_NAME  DB 16
		 DB ?
		 DB 16 DUP(0)
IN_PWD   DB 10
		 DB ?
		 DB 10 DUP(0)
IN_GOODS DB 10
	     DB ?
	     DB 10 DUP(0)
CRLF     DB 0DH,0AH,'$'
DATA ENDS

STACK SEGMENT USE16 STACK
	DB 15 DUP(0)
STACK ENDS

CODE SEGMENT USE16 
ASSUME CS:CODE,DS:DATA 
START:  
	MOV AX,STACK
	MOV SS,AX
	MOV AX,DATA 
    MOV DS,AX
	MOV SI,OFFSET S1
		
SHOP:	
	MOV DX,[SI]
	CMP DL,0
	JZ  OK
	MOV AH,2
	INT 21H
	JMP NEXT
		
NAMEINPUT:  
	LEA DX,INPUTBOSSNAME
	MOV AH,9
	INT 21H
	LEA DX,IN_NAME
	MOV AH,10
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
		
PASSWORDINPUT:  
	LEA DX,INPUTPASSWORD
	MOV AH,9
	INT 21H
	LEA DX,IN_PWD
	MOV AH,10
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H	
			
	MOV SI,OFFSET IN_NAME
	MOV DI,OFFSET BNAME
	MOV CX,[SI+1]
	MOV CH,0
	ADD SI,2
			
CHECKNAME:  
	MOV AH,[SI]
	MOV AL,[DI]
	CMP AH,AL
	JNZ NOTRIGHTNAME
	INC SI
	INC DI
	LOOP CHECKNAME
			
	MOV AH,[SI]
	CMP AH,0DH
	JNZ NOTRIGHTNAME
			
	MOV SI,OFFSET IN_PWD
	MOV DI,OFFSET BPASS
	MOV CX,[SI+1]
	MOV CH,0
	ADD SI,2
				
CHECKPWD:   
	MOV AH,[SI]
	MOV AL,[DI]
	CMP AH,AL
	JNZ NOTRIGHTPWD
	INC SI
	INC DI
	LOOP CHECKPWD
			
	MOV AH,[SI]
	CMP AH,0DH
	JNZ NOTRIGHTPWD
			
	MOV SI,OFFSET AUTH
	MOV AX,1H
	MOV [SI],AX
	LEA DX,SUCCESS
	MOV AH,9
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
			
TASK3:  
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
		MOV DI,OFFSET GA1
		PUSH DI
		MOV BX,N
		
	DEFCX:		
		MOV CX,[SI+1]
		MOV CH,0
		CMP CX,0
		JZ  NAMEINPUT
		MOV DX,DI
						
	CHECKGOODS: 
		MOV AH,[SI+2]
		MOV AL,[DI]
		CMP AH,AL
		JNZ DIF
		JMP NEXT2
											
EXIT:	
	MOV AH,4CH
	INT 21H

NEXT2:  
	INC SI
	INC DI
	DEC CX
	CMP CX,0
	JZ  FINAL
	JMP CHECKGOODS
		
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
	JZ  ISLOGIN
	JMP DIF
		
ISLOGIN: 
	MOV SI,OFFSET AUTH
	MOV AL,[SI]
	MOV SI,DX
	PUSH DX
	CMP AL,0
	JZ  CALCULATE
	JMP PRINT1
		 
CALCULATE: 
	POP DI
	PUSH DI
	MOV EDX,0
	MOV EAX,0
	MOV AX,[DI+13]
	MOV EBX,0
	MOV BL,[DI+10]
	IMUL EAX,EBX
	MOV EBX,EAX
	MOV ECX,1280D
	MOV EAX,0
	MOV AX,[DI+11]
	IMUL EAX,ECX
	CMP BX,0
	JZ  RECOMMEND
	DIV EBX
	PUSH EAX
	PUSH EDX
	MOV EDX,0
	MOV EAX,0
	MOV EBX,0
	MOV AX,[DI+17]
	MOV BX,[DI+15]
	CMP BX,0
	JZ  RECOMMEND
	MOV ECX,128D
	IMUL EAX,ECX
	DIV EBX
	POP EBX
	POP ECX
	ADD EAX,ECX
	ADD EDX,EBX
	MOV [DI+19],AX
	JMP PRINT2
		
RECOMMEND: 
	MOV AX,150D
	MOV WORD PTR[DI+19],AX
	JMP PRINT2

PRINT1:	
	MOV DL,[SI]
	CMP DL,0
	JZ  ALLIMFOR
	MOV AH,2
	INT 21H
	JMP PRINT1NEXT
		
ALLIMFOR: 
	POP DI
	PUSH DI
	MOV AH,2
	MOV DL,32
	INT 21H
	MOV DL,[DI+10]
	ADD DL,30H
	CMP DL,3AH
	JZ  TEN
	MOV AH,2
	INT 21H
	MOV CX,4
	MOV AH,2
	MOV DL,32
	INT 21H
	JMP INFORMATION
		  
TEN:	
	LEA DX,NODISCOUNT
	MOV AH,9
	INT 21H
	MOV CX,4
	JMP INFORMATION
		  
INFORMATION:	
	MOV AX,[DI+11]
	JMP DTOC
		
TONAMEINPUT:   
	MOV DX,0AH
	MOV AH,2
	INT 21H
	JMP NAMEINPUT
				
PRINT1NEXT:	
	INC SI
	JMP PRINT1

PRINT2: 
	CMP AX,99
	JA  A
	CMP AX,49
	JA  B
	CMP AX,9
	JA  C
	JMP F
		
A:		
	MOV DL,41H
	MOV AH,2
	INT 21H
	JMP TONAMEINPUT
	
B:		
	MOV DL,42H
	MOV AH,2
	INT 21H
	JMP TONAMEINPUT

C:		
	MOV DL,43H
	MOV AH,2
	INT 21H
	JMP TONAMEINPUT

F:		
	MOV DL,46H
	MOV AH,2
	INT 21H
	JMP TONAMEINPUT
	
NEXT:   
	INC SI
	JMP SHOP
		
OK:		
	MOV DX,0AH
	MOV AH,2
	INT 21H
	JMP NAMEINPUT
		
NOTRIGHTPWD:  
	LEA DX,FAIL
	MOV AH,9
	INT 21H
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP NAMEINPUT
			  
NOTRIGHTNAME: 
	MOV SI,OFFSET IN_NAME
	MOV DL,[SI+1]
	CMP DL,0
	JZ  WOR
	CMP DL,1
	JZ  ORW
	JNZ NOTRIGHTPWD
			  
ORW:		  
	MOV DL,[SI+2]
	CMP DL,'q'
	JZ  EXIT
	JNZ NOTRIGHTPWD
			  
WOR:		  
	MOV DL,[SI+2]
	CMP DL,0DH
	MOV SI,OFFSET AUTH
	MOV AX,0H
	MOV [SI],AX
	JZ  TASK3
	JMP NOTRIGHTPWD

DTOC:
	PUSH DX
	PUSH CX
	PUSH AX
	PUSH SI
	PUSH BX
	MOV BX,0	;bx在子程序中用来存放位数
	
DTOC0:
	MOV CX,10D	
	MOV DX,0
	DIV CX		;除以10
	MOV CX,AX	;得到的商赋给cx
	
	JCXZ DTOC1		;当前商为0则调到s2
	
	ADD DX,30H	;将余数加上30H得到相应的ASCII码
	PUSH DX
	
	INC BX
	
	JMP DTOC0
	
DTOC1:				;当商为0时,余数为个位
	ADD  DX,30H
	PUSH DX
	INC  BX		;再进行一次栈操作(补充当商为0而余数不为0时的情况)
	MOV  CX,BX 
	
DTOC2:				;将栈中的字符打印出来
	POP AX
	MOV DL,AL
	MOV AH,2
	INT 21H
	LOOP DTOC2
	
DTOC3:
	POP BX
	POP SI
	POP AX
	POP CX
	POP DX
	ADD DI,2
	DEC CX
	CMP CX,0
	JZ  GO
	MOV AH,2
	MOV DL,32
	INT 21H
	JMP INFORMATION
	
GO: 
	LEA DX,CRLF
	MOV AH,9
	INT 21H
	JMP GOODSINPUT
			  
CODE ENDS
END START