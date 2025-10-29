section .data
    msg db "Enter your number : ", 0
    outputMsg db "You entered: ", 0
    newline db 0xa
    
section .bss
    number resb 1

%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

section .text
    global _start

_start:
    print msg, 20
    read number, 1
    print outputMsg, 16
    print newline, 1
    
    mov eax, 1
    mov ebx, 0
    int 0x80
