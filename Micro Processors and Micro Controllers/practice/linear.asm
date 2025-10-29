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
    msg1 db 'Enter the target element : ', 10
    msglen1 equ $-msg1
    msg2 db 'The target element found at index : ', 10
    msglen2 equ $-msg2
    msg3 db 'The target element not found', 10
    msglen3 equ $-msg3
    space db ' ', 10
    space_len equ $-space
    newline db 10
    newline_len equ $-newline


section .bss
    arr resb 5
    n resb 2
    target resb 2

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
    read target, 2
    mov ecx, 5
    mov esi, 0
    mov edi, 0
    searchloop :
        push ecx
       mov al, [arr + esi]
       cmp al, target
       je found
     inc esi 
     inc edi 
        pop ecx
        loop searchloop

   found :
   print msg2, msglen2
    mov eax, edi
    add eax, '0'  
    mov [n], eax
    print n, 2
    print newline, newline_len
    jmp exit

    notfound :
    print msg3, msglen3
    print newline, newline_len
    

    exit :
    mov eax, 1
    mov ebx, 0
    int 80h
