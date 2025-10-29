section .data
    array db 5, 8, 2, 9, 1, 7, 3, 4, 6, 0    
    len equ $ - array
    msg1 db "Enter element to search: "
    msg1_len equ $ - msg1
    found_msg db "Element found at position: "
    found_len equ $ - found_msg
    not_found_msg db "Element not found in array!", 0xa
    not_found_len equ $ - not_found_msg
    newline db 0xa
    newline_len equ $ - newline

%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro input 2
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

%macro exit 0
    mov eax, 1
    mov ebx, 0
    int 0x80
%endmacro

section .bss
    search_num resb 4
    position resb 4

section .text
    global _start

_start:
    print msg1, msg1_len
    input search_num, 4
    
    mov al, [search_num]
    sub al, '0'          
    
    mov ecx, len
    mov esi, 0
    
search_loop:
    cmp al, [array + esi]
    je found
    inc esi
    loop search_loop
    
    print not_found_msg, not_found_len
    jmp exit_prog
found:
    print found_msg, found_len
    mov eax, esi          
    add eax, '0'
    mov [position], eax
    print position, 1
    print newline, newline_len

exit_prog:
    exit
