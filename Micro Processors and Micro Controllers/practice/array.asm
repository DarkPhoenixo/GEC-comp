%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro


section .data
    msg db 'Enter the elements of the array: ', 10
    msglen equ $-msg
    msg1 db 'The array element s are : ', 10
    msglen1 equ $-msg1
    space db ' ', 10
    space_len equ $-space
    newline db 10
    newline_len equ $-newline


section .bss
    arr resb 5
    n resb 2

    section .text
    global _start
    _start:
    print msg, msglen
    mov ecx, 5
    mov esi, 0

    readloop :
        push ecx
        read n,2
        mov al, [n]
        sub al, '0'  ; 
        mov [arr + esi], al
        inc esi
        pop ecx
        loop readloop


    print msg1, msglen1
    mov ecx, 5
    mov esi, 0
    printloop :
        push ecx
       mov al, [arr + esi]
        add al, '0'  
        mov [n], al
        print n, 2
        print space, space_len
        inc esi
        pop ecx
        loop printloop

    print newline, newline_len
    mov eax, 1
    mov ebx, 0
    int 80h
