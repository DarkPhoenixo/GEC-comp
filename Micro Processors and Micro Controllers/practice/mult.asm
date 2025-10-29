%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
    %endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
    %endmacro

    section .data
    msg db 'Enter the first number: ', 10
    msglen equ $-msg
    msg1 db 'Enter the second number: ', 10
    msglen1 equ $-msg1
    msg2 db 'The sum of numbers is: ', 10
    msglen2 equ $-msg2
    msg3 db 'The number of digits in the  number is: ', 10
    msglen3 equ $-msg3
    newline db 10
    newline_len equ $-newline


    section .bss
    num1 resb 100
    num2 resb 100
    result resb 100
    ndig resb 2

    section .text
    global _start
    _start:
           print msg3, msglen3
    read ndig, 2
    print msg, msglen
    read num1, 100
    print msg1, msglen1
    read num2, 100

    mov ecx ,byte [ndig]
    sub ecx, '0'  ; 
    mov esi ,ecx
    dec esi 
    call add 
    print msg2, msglen2
    print result, 100
    print newline, newline_len
     mov eax, 1
    mov ebx, 0
    int 80h


    add:
        mov al,[num1+esi]
        mov bl,[num2+esi]
        adc al,bl
        aaa
        pushf
        or al,30h
        popf
        mov [result+esi],al
        dec esi
        loop add
        ret