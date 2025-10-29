%macro print 2
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

section .data
    prompt db "Enter string  : "
    asc_msg db "Ascending: "
    desc_msg db "Descending: "
    newline db 10

section .bss
    string resb 100
    string2 resb 100
    string_len resd 1

section .text
global _start

_start:
    print prompt, 12
    read string, 100
    dec eax
    mov [string_len], al


    mov ecx, eax
    mov esi, string
    mov edi, string2
    cld
    rep movsb

    
    mov ecx, [string_len]
    dec ecx                    
outer_loop_asc:
    push ecx
    mov esi, string
    mov ecx, [string_len]
    dec ecx                   
inner_loop_asc:
    mov al, [esi]
    mov bl, [esi + 1]
    cmp al, bl
    jle skip_swap_asc
    mov [esi], bl
    mov [esi + 1], al
skip_swap_asc:
    inc esi
    dec ecx
    jnz inner_loop_asc
    pop ecx
    
    mov ecx, [string_len]
    dec ecx                     
outer_loop_desc:
    push ecx
    mov esi, string2
    mov ecx, [string_len]
    dec ecx                    
inner_loop_desc:
    mov al, [esi]
    mov bl, [esi + 1]
    cmp al, bl
    jge skip_swap_desc
    mov [esi], bl
    mov [esi + 1], al
skip_swap_desc:
    inc esi
    dec ecx
    jnz inner_loop_desc
    pop ecx
    loop outer_loop_desc
    pop ecx
    loop outer_loop_desc

    print asc_msg, 11
    print string, [string_len]
    print newline, 1

    print desc_msg, 11
    print string2, [string_len]
    print newline, 1

    mov eax, 1
    xor ebx, ebx
    int 80h
