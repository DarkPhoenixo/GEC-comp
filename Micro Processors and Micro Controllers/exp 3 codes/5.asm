section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Num: '
msg1Len equ $-msg1
msg2 db 'Next 4 numbers are: '
msg2Len equ $-msg2

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


section .bss
num RESB 8

section .text
global _start
_start:

writesystem msg1,msg1Len

readsystem num,8
writesystem msg2,msg2Len
writesystem msg, msgLen

mov eax,[num]
sub eax,'0'
inc eax
add eax,'0'
mov [num],eax
writesystem num,1
writesystem msg, msgLen
mov eax,[num]
sub eax,'0'
inc eax
add eax,'0'
mov [num],eax
writesystem num,1
writesystem msg, msgLen
mov eax,[num]
sub eax,'0'
inc eax
add eax,'0'
mov [num],eax
writesystem num,1
writesystem msg, msgLen
mov eax,[num]
sub eax,'0'
inc eax
add eax,'0'
mov [num],eax
writesystem num,1
writesystem msg, msgLen

mov eax, 1
mov ebx, 0
int 80h 
 

