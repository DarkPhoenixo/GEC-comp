%macro writenumber 2
    mov ecx, %1
    mov edx, %2
    mov ebx, 1
    mov eax, 4
    int 80h
%endmacro

section .data
    msg db "Atharv", 010
    len equ $ - msg

section .text
global _start
_start:
    mov esi, 0
    loop:
    push esi
    writenumber msg, len
    pop esi
    inc esi
    cmp esi, 7
    jl loop

end:
mov eax, 1
mov ebx,0
int 80h
