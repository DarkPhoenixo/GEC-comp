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
    msg2 db 'The number is less than 5 ',10
    msglen2 equ $-msg2
     msg2 db 'The number is greater than 5 ',10
    msglen2 equ $-msg2
     msg2 db 'The number is equal than 5 ',10
    msglen2 equ $-msg2
    space db ' ', 10
    space_len equ $-space
    newline db 10
    newline_len equ $-newline


section .bss
    arr resb 5
    n resb 2
    eqfive resb 1
    grfive resb 1
    lsfive resb 1

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


   
    mov ecx, 5
    mov esi, 0
    mov byte[eqfive],0
      mov byte[grfive],0
        mov byte[lsfivefive],0
    printloop :
        push ecx
       mov al, [arr + esi]
        cmp al,5
        jl lesser
        jg greater
       inc [eqfive]
       jmp continue 

       greater :
       inc [grfive]
       jmp continue

       lesser :
       inc [lsfive]

       continue :
       inc esi 
       pop ecx
       loop readloop

       
    print newline, newline_len
    mov eax, 1
    mov ebx, 0
    int 80h
