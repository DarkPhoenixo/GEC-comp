section .data
    array db 5, 8, 2, 9, 1, 7, 3, 4, 6, 0    
    len equ $ - array
    msg1 db "Ascending order: ", 0xa
    msg1_len equ $ - msg1
    msg2 db "Descending order: ", 0xa
    msg2_len equ $ - msg2
    space db " "
    newline db 0xa

section .bss
    temp resb 1
    digit resb 1

section .text
global _start


%macro print 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 0x80
%endmacro

_start:
    mov ecx, len        
outer_loop_asc:
    push ecx
    mov esi, 0
    mov ecx, len
    dec ecx

inner_loop_asc:
    mov al, [array + esi]
    mov bl, [array + esi + 1]
    cmp al, bl
    jle no_swap_asc

    mov [temp], al
    mov al, bl
    mov bl, [temp]
    mov [array + esi], al
    mov [array + esi + 1], bl

no_swap_asc:
    inc esi
    loop inner_loop_asc
    pop ecx
    loop outer_loop_asc

    print newline, 1
    print msg1, msg1_len
    mov esi, 0
print_loop1:
    mov al, [array + esi]
    add al, '0'
    mov [digit], al
    print digit, 1
    print space, 1
    inc esi
    cmp esi, len
    jl print_loop1
    
    print msg1, 1   
    mov ecx, len        
outer_loop_desc:
    push ecx
    mov esi, 0
    mov ecx, len
    dec ecx

inner_loop_desc:
    mov al, [array + esi]
    mov bl, [array + esi + 1]
    cmp al, bl
    jge no_swap_desc

    mov [temp], al
    mov al, bl
    mov bl, [temp]
    mov [array + esi], al
    mov [array + esi + 1], bl

no_swap_desc:
    inc esi
    loop inner_loop_desc
    pop ecx
    loop outer_loop_desc

    print newline, 1
    print msg2, msg2_len
    mov esi, 0
print_loop2:
    mov al, [array + esi]
    add al, '0'
    mov [digit], al
    print digit, 1
    print space, 1
    inc esi
    cmp esi, len
    jl print_loop2
    print msg2, 1    
    mov eax, 1
    mov ebx, 0
    int 0x80
    int 0x80
