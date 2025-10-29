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
    msg db 'Enter the elements of the array with negative signs: ', 10
    msglen equ $-msg
    msg1 db 'The array element s are : ', 10
    msglen1 equ $-msg1
    msg2 db 'The number of negative elements is: ', 10
    msglen2 equ $-msg2
    msg3 db 'The number of positive elements is: ', 10
    msglen3 equ $-msg3
    space db ' ', 10
    space_len equ $-space
    newline db 10
    newline_len equ $-newline


section .bss
    arr resb 5
    n resb 3
    neg_count resb 1
    pos_count resb 1

    section .text
    global _start
    _start:
    print msg, msglen
    mov ecx, 5
    mov esi, 0

    readloop :
        push ecx
        read n,3
        mov al, [n]
        cmp al, '-';
        je negative 
        inc [pos_count]
        mov [arr + esi], al
        inc esi
        pop ecx
        loop readloop

    negative:
        inc [neg_count]
        mov al, [n + 1]  
        mov [arr + esi], al
        inc esi
        pop ecx
        loop readloop


 print msg2, msglen2
 mov al, [neg_count]
    mov [n], al
    print n, 2

    print msg3, msglen3
    mov al, [pos_count]
    mov [n], al
    print n, 2
    print msg1, msglen1
 

    print newline, newline_len
    mov eax, 1
    mov ebx, 0
    int 80h
