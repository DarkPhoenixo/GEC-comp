%macro write 2
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

%macro ADD 2
    movzx eax, byte [%1]
    sub al, '0'
    movzx ebx, byte [%2]
    sub bl, '0'
    add eax, ebx
    add al, '0'
    mov [result], al
%endmacro

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
_start:
    write prompt, prompt_len
    read n, 2
    write msg, msg_len
    mov byte [num1], '0'
    mov byte [num2], '1'
    movzx ecx, byte [n]
    sub ecx, '0'
    loop:
    push ecx
    write num1, 1
    write space, 1
    ADD num1, num2
    mov al, [num2]
    mov [num1], al
    mov al, [result]
    mov [num2], al
    pop ecx
    dec ecx
    jnz loop
    write newline, 1
mov eax, 1
mov ebx,0
int 80h