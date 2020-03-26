.386
.model flat, c

;long asmTest(char *szMsg)
public asmTest

MessageBoxA proto stdcall :dword,:dword, :dword,:dword
printf	    proto cdecl   :dword
sum         proto cdecl   :dword, :dword

includelib  user32.lib
includelib  kernel32.lib

.data
 szTopic   db  "asmTest(char *szMsg)",0
 
.code

asmTest  proc   addrMsg:dword
	 invoke MessageBoxA,0,addrMsg,offset szTopic,0  ;Call Windows API
	 invoke printf, addrMsg                         ;Call printf() in C++
	 invoke sum, 100, 200                           ;Call sum() in C++
	 ret					        ;(EAX) = 300
asmTest  endp

	 end
