section .data
    msg1 db "Enter first number : ", 0xa
    msg2 db "Enter second number : ", 0xa
    result_msg db "Your printed number is : ", 0xa
    msg3 db "First number is: ", 0xa
    msg4 db "Second number is: ", 0xa
    newline db 0xa
    space db " "

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
    
section .bss
    num1 resb 2
    num2 resb 2





section .text
    global _start

_start:
    print msg1, 19
    
    read num1, 2
    print space, 1
    print result_msg, 22
    print space, 1
    print num1, 2
    
    print msg2, 19
    print space, 1
    read num2, 2
    print result_msg, 22
    print space, 1
    print num2, 2
    
    mov eax, 1
    mov ebx, 0
    int 0x80
