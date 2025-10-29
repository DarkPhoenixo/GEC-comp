section.data
msg db "hello",10
msglen equ $-msg

section.bss
num1 resb 5 

section.text
global _start
_start :
mov eax 4
mov ebx 1
mov ecx msg
mov edx msglen
int 80h

mov eax 3 
mov ebx 0
mov ecx num1
mov edx 5
int 80h
mov eax 1
mov ebx 0
int 80h
