%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro read 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

section .data
    prompt db 'Enter password: ', 0
    prompt_len equ $ - prompt
    correct_msg db 'Correct password!', 0xa
    correct_len equ $ - correct_msg
    wrong_msg db 'Wrong password!', 0xa
    wrong_len equ $ - wrong_msg
    password db 'SE_COMP', 0
    pass_len equ $ - password - 1

section .bss
    input resb 100
    input_len resb 1

section .text
    global _start

_start:
    print prompt, prompt_len
    read input, 100
    mov [input_len], eax
    dec byte [input_len]

    mov al, [input_len]
    cmp al, pass_len
    jne wrong_password

    mov ecx, pass_len
    mov esi, password
    mov edi, input
    
compare_loop:
    mov al, [esi]
    mov bl, [edi]
    cmp al, bl
    jne wrong_password
    inc esi
    inc edi
    dec ecx
    jnz compare_loop
    
    print correct_msg, correct_len
    jmp exit

wrong_password:
    print wrong_msg, wrong_len

exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
