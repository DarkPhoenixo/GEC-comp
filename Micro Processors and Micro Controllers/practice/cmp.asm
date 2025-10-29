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
    msg2 db 'Enteer the third number: ', 10
    msglen2 equ $-msg2
    msg3 db 'All numbers are equal', 10
    msglen3 equ $-msg3
    msg4 db 'The first number is greater than the second and third', 10
    msglen4 equ $-msg4
    msg5 db 'The second number is greater than the first and third', 10
    msglen5 equ $-msg5
    msg6 db 'The third number is greater than the first and second', 10
    msglen6 equ $-msg6
    space db ' ', 10
    space_len equ $-space
    newline db 10

    section .bss
    num1 resb 100
    num2 resb 100
    num3 resb 100

section .text
global _start
_start:
    print msg, msglen
    read num1, 100
    print msg1, msglen1
    read num2, 100
    print msg2, msglen2
    read num3, 100

    mov al, [num1]
    mov bl, [num2]
    mov cl, [num3]
    sub al, '0'
    sub bl, '0'
    sub cl, '0'

    cmp al, bl
    jne find_greatest
    cmp bl, cl
    jne find_greatest
    print msg3, msglen3
    jmp exit 

find_greatest:
    cmp al, bl
    jg check_second
    cmp bl, cl
    jg second_greater
    jmp third_greater


    check_second:
    cmp al, cl
    jg first_greater
    jmp third_greater

first_greater:
    print msg4, msglen4
    jmp exit
second_greater:
    print msg5, msglen5
    jmp exit
third_greater:
    print msg6, msglen6
    jmp exit
exit:
    mov eax, 1
    mov ebx, 0
    int 80h
    