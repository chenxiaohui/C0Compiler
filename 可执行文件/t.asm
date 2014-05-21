.386
.model flat,stdcall
option casemap:none
includelib msvcrt.lib
printf   PROTO C :dword,:vararg
scanf    PROTO  C :dword,:vararg
.data
STR0  sbyte    ' move to ',0ah,0
STR1  sbyte    'please input the numbers of disks: ',0ah,0
STR2  sbyte    'the step of moving disks: ',0ah,0
STR_format sbyte '%d',0
.code
_MOVE_1  proc  C _F:dword,_T:dword;使用堆栈传递参数,C规则
invoke printf,offset STR_format,_F
invoke printf, offset STR0
invoke printf,offset STR_format,_T
ret
_MOVE_1 endp
_MOVE_N  proc  C _M:dword,_A:dword,_B:dword,_C:dword;使用堆栈传递参数,C规则
local T0,T1,T2,T3,T4,T5:dword
mov eax,_M
cmp eax,1
jz  LP0
jmp  LP1
LP0:
invoke _MOVE_1,_A,_C
mov T0,eax
jmp  LP2
LP1:
mov eax,_M
sub eax,1
mov T1,eax
invoke _MOVE_N,T1,_A,_C,_B
mov T2,eax
invoke _MOVE_1,_A,_C
mov T3,eax
mov eax,_M
sub eax,1
mov T4,eax
invoke _MOVE_N,T4,_B,_A,_C
mov T5,eax
LP2:
ret
_MOVE_N endp
main  proc 
local _N,T6:dword
invoke printf, offset STR1
invoke scanf,offset STR_format,addr _N
invoke printf, offset STR2
invoke printf,offset STR_format,_N
invoke _MOVE_N,_N,1,2,3
mov T6,eax
ret
main endp
end main
