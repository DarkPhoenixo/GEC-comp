section.data 
msg1 db "Enter the number", 10
msglen equ $-msg1
msg2 db "The number is: ", 10
msg2len equ $-msg2

section.bss
num resb 100

section.text
global _start

_start:
    call print
    mov ecx, msg1
    mov edx, msglen
    int 80h

    call read
    mov ecx, num
    mov edx, 100
    int 80h
    call print_num
    mov ecx, msg2
    mov edx, msg2len
    int 80h

    call exit


    print :
    mov eax, 4
    mov ebx, 1
    ret 

    read :
    mov eax, 3
    mov ebx, 0
    ret

    print_num :
    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, 100
    int 80h
    ret

    exit :
    mov eax, 1
    xor ebx, ebx
    int 80h
    ret