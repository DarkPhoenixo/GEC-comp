SECTION .DATA
hello db 'Hello World', 10
hellolen equ $ - hello

SECTION .TEXT
GLOBAL _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, hello
    mov edx, hellolen
    int 80h

    mov eax, 1
    xor ebx, ebx
    int 80h
