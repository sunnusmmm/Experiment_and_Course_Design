.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD

include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

student	     struct
	     product   db  10 dup(0)
	     discount  db  0
	     inPrice     dw  0
	     salePrice  dw  0
	     inGoods  dw  0
	     sold    dw  0
		 recommend   dw  0
student      ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'Our First Window',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'I am CS1707 聂鸿勇',0
hInstance    dd       0
CommandLine  dd       0
buf	     student  <'PEN       ',10,35,56,1000,32,0>
		 student  <'APPLE     ',8,2,4,40,25,0>
		 student  <'BOOK      ',9,12,30,180,5,0>
		 student  <'SHOES     ',8,16,25,500,4,0>
msg_product     db       'product',0
msg_discount  db       'discount',0
msg_inPrice     db       'inPrice',0
msg_salePrice  db       'salePrice',0
msg_inGoods  db       'inGoods',0
msg_sold    db       'sold',0
msg_recommend		db		'recommend',0
menuItem     db       0  ;当前菜单状态, 1=处于list, 0=Clear
NUMBER db 5 dup(' ')

.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
	     LOCAL  ps:PAINTSTRUCT
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
	    .ELSEIF wParam == IDM_Action_Recommendation
		    call RECCOMEND_CAL
	    .ELSEIF wParam == IDM_Action_LIST
		    mov menuItem, 0
		    invoke InvalidateRect,hWnd,0,1  ;擦除整个客户区
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
             invoke BeginPaint,hWnd, addr ps
             mov hdc,eax
	     .IF menuItem == 0
		 invoke Display,hdc
	     .ENDIF
	     invoke EndPaint,hWnd,addr ps
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display      proc   hdc:HDC
             XX     equ  10
             YY     equ  10
	     XX_GAP equ  100
	     YY_GAP equ  30
             invoke TextOut,hdc,XX+0*XX_GAP,YY+0*YY_GAP,offset msg_product,7
             invoke TextOut,hdc,XX+1*XX_GAP,YY+0*YY_GAP,offset msg_discount,8
             invoke TextOut,hdc,XX+2*XX_GAP,YY+0*YY_GAP,offset msg_inPrice,7
             invoke TextOut,hdc,XX+3*XX_GAP,YY+0*YY_GAP,offset msg_salePrice,9
             invoke TextOut,hdc,XX+4*XX_GAP,YY+0*YY_GAP,offset msg_inGoods,7
             invoke TextOut,hdc,XX+5*XX_GAP,YY+0*YY_GAP,offset msg_sold,4
			 invoke TextOut,hdc,XX+6*XX_GAP,YY+0*YY_GAP,offset msg_recommend,9
             ;;
			 MOV CX,0
			 mov esi,YY+1*YY_GAP
			 mov edi,0
		P:	 push cx
			 invoke TextOut,hdc,XX+0*XX_GAP,esi,addr buf[edi].product,10
			 mov al,buf[edi].discount
			 mov ah,0
			 call DTOC
             invoke TextOut,hdc,XX+1*XX_GAP,esi,offset NUMBER,5
			 mov ax,buf[edi].inPrice
			 call DTOC
             invoke TextOut,hdc,XX+2*XX_GAP,esi,offset NUMBER,5
			 mov ax,buf[edi].salePrice
			 call DTOC
             invoke TextOut,hdc,XX+3*XX_GAP,esi,offset NUMBER,5
			 mov ax,buf[edi].inGoods
			 call DTOC
             invoke TextOut,hdc,XX+4*XX_GAP,esi,offset NUMBER,5
			 mov ax,buf[edi].sold
			 call DTOC
             invoke TextOut,hdc,XX+5*XX_GAP,esi,offset NUMBER,5
			 mov ax,buf[edi].recommend
			 call DTOC
             invoke TextOut,hdc,XX+6*XX_GAP,esi,offset NUMBER,5
			 add esi,30
			 add edi,21
			 pop cx
			 inc cx
			 cmp cx,4
			 jnz P
			 
             ret
Display      endp

DTOC PROC               ;将数字转换为字符串输出
	PUSH eDX
	PUSH eCX
	PUSH eSI
	PUSH eBX
	MOV BX,0	
DTOC0:
	MOV CX,10
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
	mov  esi, 0
DTOC2:
    cmp bx, 0
    je DTOC3
	POP AX
	MOV NUMBER[esi],AL
	inc esi
    dec bx
	jmp DTOC2
DTOC3:
	cmp esi, 5
	jae DTOC_EXIT
	mov NUMBER[esi], ' '
	inc esi
	jmp DTOC3
DTOC_EXIT:
	POP eBX
	POP eSI
	POP eCX
	POP eDX
	ret
DTOC ENDP


RECCOMEND_CAL PROC NEAR		        ;计算推荐度
        push edi
        push ecx
        push ebx
        push eax
        push edx
        push esi
        mov edi, OFFSET buf
        mov ecx, 4
CAL_REC:
        movzx ebx, WORD PTR 11[edi]      ;进货价
        imul ebx, 1280
        movzx eax, WORD PTR 13[edi]
        cmp BYTE PTR 10[edi], 0
        je FREE_GOOD
        cmp WORD PTR 13[edi], 0
        je FREE_GOOD

        mov edx, 0
        mul BYTE PTR 10[edi]
        sal edx, 16
        mov dx, ax                      ;销售价*折扣
        mov esi, edx
        mov edx, 0
        mov eax, ebx
        DIV esi
P2:
        push eax
        mov edx, 0 
        movzx eax, WORD PTR 17[edi]      ;出售数量
        sal eax, 7
        movzx esi, WORD PTR 15[edi]      ;进货数量
        DIV esi
        pop esi
        add eax, esi
        mov 19[edi], ax
        add edi, 21
        loop CAL_REC

        pop esi
        pop edx
        pop eax
        pop ebx
        pop ecx
        pop edi
	ret
FREE_GOOD:
        mov eax, 0
        jmp P2
RECCOMEND_CAL ENDP

             end  Start
