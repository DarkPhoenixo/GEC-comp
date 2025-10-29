section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Num1: '
msg1Len equ $-msg1
msg2 db 'Num2: '
msg2Len equ $-msg2
msg3 db 'Num3: '
msg3Len equ $-msg3
msg4 db 'Sum= '
msg4Len equ $-msg4

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

%macro SUM 3
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
add eax,ebx
mov ebx,[num3]
sub ebx, '0'
add eax,ebx
add eax, '0'
mov [sum], eax
%endmacro

section .bss
num1 RESB 8
num2 RESB 8
num3 RESB 8
sum RESB 8

section .text
global _start
_start:

writesystem msg1,msg1Len
readsystem num1,8
writesystem msg2,msg2Len
readsystem num2,8
writesystem msg3,msg3Len
readsystem num3,8

SUM num1,num2,num3
writesystem msg4,msg4Len
writesystem sum,1
writesystem msg, msgLen
mov eax, 1
mov ebx, 0
int 80h 