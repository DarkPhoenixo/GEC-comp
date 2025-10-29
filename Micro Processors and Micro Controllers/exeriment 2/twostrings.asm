SECTION .DATA
str1 db 'First String', 10
str2 db 'Second String', 10
str1len equ $ - str1
str2len equ $ - str2

SECTION .TEXT
GLOBAL _start

_start:
    ; Print the first string
    mov eax, 4
    mov ebx, 1
    mov ecx, str1
    mov edx, str1len
    int 80h

    ; Print the second string
    mov eax, 4
    mov ebx, 1
    mov ecx, str2
    mov edx, str2len
    int 80h

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 80h
