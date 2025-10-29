section .data
    message1 db "Enter first value: ", 0
    message2 db "Enter second value: ", 0
    output1 db "First value: ", 0
    output2 db "Second value: ", 0
    newline db 0xa
    space db " "

section .bss
    value1 resb 32
    value2 resb 32

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

%macro exit 0
    mov eax, 1
    mov ebx, 0
    int 0x80
%endmacro

section .text
    global _start

_start:
    print message1, 17
    print space, 1
    read value1, 32
    
    print message2, 18
    print space, 1
    read value2, 32
    
    print output1, 12
    print space, 1
    print value1, 32
    print newline, 1
    
    print output2, 13
    print space, 1
    print value2, 32
    
    exit
