section .data
    prompt db 'Enter n: '
    prompt_len equ $ - prompt
    msg db 'Series: '
    msg_len equ $ - msg
    space db ' '
    newline db 10

section .bss
    n resb 2
    num1 resb 2
    num2 resb 2
    result resb 2

section .text
global _start

write_proc:
    push ebp
    mov ebp, esp
    mov eax, 4
    mov ebx, 1
    mov ecx, [ebp+12]
    mov edx, [ebp+8]
    int 80h
    mov esp, ebp
    pop ebp
    ret 8

read_proc:
    push ebp
    mov ebp, esp
    mov eax, 3
    mov ebx, 0
    mov ecx, [ebp+12]
    mov edx, [ebp+8]
    int 80h
    mov esp, ebp
    pop ebp
    ret 8

add_proc:
    push ebp
    mov ebp, esp
    movzx eax, byte [ebp+12]
    sub al, '0'
    movzx ebx, byte [ebp+8]
    sub bl, '0'
    add eax, ebx
    add al, '0'
    mov [result], al
    mov esp, ebp
    pop ebp
    ret 8

_start:
    push prompt
    push prompt_len
    call write_proc

    push n
    push 2
    call read_proc

    push msg
    push msg_len
    call write_proc

    mov byte [num1], '0'
    mov byte [num2], '1'
    movzx ecx, byte [n]
    sub ecx, '0'

loop:
    push ecx
    
    push num1
    push 1
    call write_proc

    push space
    push 1
    call write_proc

    push dword [num1]
    push dword [num2]
    call add_proc

    mov al, [num2]
    mov [num1], al
    mov al, [result]
    mov [num2], al
    
    pop ecx
    dec ecx
    jnz loop

    push newline
    push 1
    call write_proc

    mov eax, 1
    mov ebx, 0
    int 80h