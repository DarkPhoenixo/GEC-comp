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

section .data
    main_menu db 10, "STACK OPTIONS:", 10
              db "1. Add ", 10
              db "2. Remove ", 10
              db "3. Show Top ", 10
              db "4. Quit", 10
              db "Select option: ", 0
    menu_size equ $ - main_menu

    input_prompt db 10, "Input value: ", 0
    input_len equ $ - input_prompt

    pop_notice db 10, "Removed value: ", 0
    pop_size equ $ - pop_notice

    top_notice db 10, "Current top: ", 0
    top_size equ $ - top_notice

    empty_stack_msg db 10, "No items in stack!", 10, 0
    empty_size equ $ - empty_stack_msg

    full_stack_msg db 10, "Stack limit reached!", 10, 0
    full_size equ $ - full_stack_msg

    content_header db 10, "Stack [Top -> Bottom]: ", 0
    content_len equ $ - content_header

    newline_char db 10
    blank_space db " "

section .bss
    stack_mem resw 9
    pointer_top resw 1
    opt_choice resb 2
    read_buffer resb 20
    print_buffer resb 20

section .text
    global _start

_start:
    mov word [pointer_top], -1

menu_main:
    print main_menu, menu_size
    input opt_choice, 2

    mov al, [opt_choice]
    sub al, '0'

    cmp al, 1
    je action_push

    cmp al, 2
    je action_pop

    cmp al, 3
    je show_top

    cmp al, 4
    je terminate

    jmp menu_main

action_push:
    mov ax, [pointer_top]
    cmp ax, 8
    jl allow_push

    print full_stack_msg, full_size
    jmp menu_main

allow_push:
    print input_prompt, input_len
    input read_buffer, 10

    mov eax, 0
    mov ecx, 0

convert_input:
    mov bl, byte [read_buffer + ecx]
    cmp bl, 10
    je done_input
    cmp bl, 0
    je done_input

    sub bl, '0'
    imul eax, 10
    add eax, ebx

    inc ecx
    jmp convert_input

done_input:
    inc word [pointer_top]
    movzx ebx, word [pointer_top]
    mov [stack_mem + ebx*2], ax
    jmp show_stack

action_pop:
    mov ax, [pointer_top]
    cmp ax, -1
    jg ok_pop

    print empty_stack_msg, empty_size
    jmp menu_main

ok_pop:
    print pop_notice, pop_size

    movzx ebx, word [pointer_top]
    movzx eax, word [stack_mem + ebx*2]

    mov ecx, print_buffer
    add ecx, 19
    mov byte [ecx], 0

    mov ebx, 10

convert_pop_val:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz convert_pop_val

    push ecx
    mov edx, print_buffer
    add edx, 19
    sub edx, ecx
    print ecx, edx
    pop ecx

    print newline_char, 1

    dec word [pointer_top]
    jmp show_stack

show_top:
    mov ax, [pointer_top]
    cmp ax, -1
    jg top_found

    print empty_stack_msg, empty_size
    jmp menu_main

top_found:
    print top_notice, top_size

    movzx ebx, word [pointer_top]
    movzx eax, word [stack_mem + ebx*2]

    mov ecx, print_buffer
    add ecx, 19
    mov byte [ecx], 0

    mov ebx, 10

conv_top_val:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz conv_top_val

    push ecx
    mov edx, print_buffer
    add edx, 19
    sub edx, ecx
    print ecx, edx
    pop ecx

    print newline_char, 1

    jmp menu_main

show_stack:
    print content_header, content_len

    movsx eax, word [pointer_top]
    cmp eax, -1
    jle no_elements

    mov edi, eax

stack_loop:
    cmp edi, -1
    jle stack_done

    movzx eax, word [stack_mem + edi*2]
    push edi

    mov ecx, print_buffer
    add ecx, 19
    mov byte [ecx], 0

    mov ebx, 10

conv_stack_val:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz conv_stack_val

    push ecx
    mov edx, print_buffer
    add edx, 19
    sub edx, ecx
    print ecx, edx
    pop ecx

    print blank_space, 1

    pop edi
    dec edi
    jmp stack_loop

stack_done:
    print newline_char, 1
    jmp menu_main

no_elements:
    print empty_stack_msg, empty_size
    jmp menu_main

terminate:
    mov eax, 1
    xor ebx, ebx
    int 0x80
