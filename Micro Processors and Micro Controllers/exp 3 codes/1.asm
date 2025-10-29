section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Number 1: '
msg1Len equ $-msg1
msg2 db 'Number 2: '
msg2Len equ $-msg2
msg3 db 'Sum: '
msg3Len equ $-msg3

%macro writesystem 2
mov eax,4
mov ebx,1
mov ecx, %1
mov edx, %2
int 80h
%endmacro
%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro
%macro addition 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
add eax, ebx
add eax, '0'
mov [sum], eax
%endmacro
section .bss
num1 RESB 5
num2 RESB 5
sum RESB 5
section .text
global _start
_start:
writesystem msg1,msg1Len
readsystem num1,5
writesystem msg2,msg2Len
readsystem num2,5
addition num1,num2
writesystem msg3,msg3Len
writesystem sum,1
writesystem msg, msgLen
mov eax, 1
mov ebx, 0
int 80h 
