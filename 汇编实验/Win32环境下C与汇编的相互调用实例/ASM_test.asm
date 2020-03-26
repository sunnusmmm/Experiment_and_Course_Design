.386
.model flat, c

;long asmTest(char *szMsg)
public asmTest

MessageBoxA proto stdcall :dword,:dword, :dword,:dword
extrn printf :near
extrn sum    :near

includelib  user32.lib
includelib  kernel32.lib

.data
 szTopic   db  "asmTest(char *szMsg)",0
 
.code

asmTest  proc near
	 push ebp
	 mov  ebp, esp
	 ;;
	 ;;Call Windows API
	 push dword ptr 0
	 push dword ptr offset szTopic
	 push dword ptr [ebp+8]  ;szMsg
	 push dword ptr 0
	 call MessageBoxA
	 ;;stdcall does not need "add  esp, 16"
	 ;;
	 ;;Call printf() in C++
	 push dword ptr [ebp+8]  ;szMsg
	 call printf
	 add  esp, 4             ;cdecl needs "add esp, 4"
	 ;;
	 ;;Call sum(long a,long b) in C++
	 push dword ptr 200
	 push dword ptr 100
	 call sum 
	 add  esp, 8             ;cdecl needs "add esp, 8"
	 ;;
	 pop  ebp
	 ret
asmTest  endp
	 end
