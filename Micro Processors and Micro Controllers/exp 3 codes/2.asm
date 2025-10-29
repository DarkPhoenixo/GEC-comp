section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Number 1: '
msg1Len equ $-msg1
msg2 db 'Number 2: '
msg2Len equ $-msg2
msg3 db 'Sum: '
msg3Len equ $-msg3
msg4 db 'Difference: '
msg4Len equ $-msg4
msg5 db 'Product: '
msg5Len equ $-msg5
msg6 db 'Quotient: '
msg6Len equ $-msg6
msg7 db 'Remainder: '
msg7Len equ $-msg7

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

%macro subtraction 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
sub eax, ebx
add eax, '0'
mov [diff], eax
%endmacro

%macro multiplication 2
mov eax, [num1]
sub eax, '0'
mov ebx, [num2]
sub ebx, '0'
mul ebx
add eax, '0'
mov [prod], eax
%endmacro

%macro division 2
mov al, [num1]
sub al, '0'
mov bl, [num2]
sub bl, '0'
div bl
add al, '0'
mov [quot], al
add ah, '0'
mov [rem], ah
%endmacro

section .bss
num1 RESB 5
num2 RESB 5
sum RESB 5
diff RESB 5
prod RESB 5
quot RESB 5
rem RESB 5
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
subtraction num1,num2
writesystem msg4,msg4Len
writesystem diff,1
writesystem msg, msgLen
multiplication num1,num2
writesystem msg5,msg5Len
writesystem prod, 1
writesystem msg, msgLen
division num1,num2
writesystem msg6,msg6Len
writesystem quot, 1
writesystem msg, msgLen
writesystem msg7,msg7Len
writesystem rem, 1
writesystem msg, msgLen
mov eax, 1
mov ebx, 0
int 80h 
