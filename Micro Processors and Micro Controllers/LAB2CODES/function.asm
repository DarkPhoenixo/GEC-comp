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
    prompt db 'Enter a string: ', 0
    prompt_len equ $ - prompt
    newline db 0xa
    newline_len equ $ - newline
    output_msg db 'You entered: ', 0
    output_msg_len equ $ - output_msg

section .bss
    string resb 100
    strlen resb 1

section .text
    global _start

read_string:
    print prompt, prompt_len
    read string, 100
    mov [strlen], eax
    ret

display_string:
    print output_msg, output_msg_len
    print string, [strlen]
    print newline, newline_len
    ret

_start:
    call read_string
    call display_string

    mov eax, 1
    mov ebx, 0
    int 0x80
