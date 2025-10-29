section .data

    outputMsg db "You entered: ", 0
    newline db 0xa

    %macro print 2
        mov eax, 4
        mov ebx, 1
        mov ecx, %1
        mov edx, %2
        int 0x80
    %endmacro
    
number db '5'   

section .text
    global _start

_start:
    print outputMsg, 16
    print newline, 1
    
    mov eax, 1
    mov ebx, 0
    int 0x80
