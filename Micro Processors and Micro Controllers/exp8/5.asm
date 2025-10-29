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
    msg db 'Enter the elements o3f the array: ', 0xA
    plen equ $ - msg
    msg1 db 'The array elements are: '
    mlen equ $ - msg1
    msg2 db 'Sum of elements: '
    slen equ $ - msg2
    space db ' '
    splen equ $ - space
    newline db 0xA
    nlen equ $ - newline

section .bss
    array resd 5
    num resb 6
    sum resd 1
    dispbuf resb 6

section .text
    global _start

_start:
    mov ecx, 5
    mov esi, 0
    
    push ecx
    print msg, plen
    pop ecx

input_loop:
    push ecx
    read num, 6
    
    mov ebx, 0
    mov ecx, 0
convert:
    mov al, [num + ecx]
    cmp al, 0xA
    je done_convert
    sub al, '0'
    imul ebx, 10
    add bl, al
    inc ecx
    jmp convert
    
done_convert:
    mov [array + esi*4], ebx
    add esi, 1
    pop ecx
    loop input_loop

    mov ecx, 5
    mov esi, 0
    mov ebx, 0
sum_loop:
    add ebx, [array + esi*4]
    add esi, 1
    loop sum_loop
    mov [sum], ebx

    print msg1, mlen
    mov ecx, 5
    mov esi, 0
display_loop:
    push ecx
    mov eax, [array + esi*4]
    
    mov ecx, dispbuf
    add ecx, 5
    mov byte [ecx], 0
    mov ebx, 10
convert_to_ascii:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz convert_to_ascii
    
    print ecx, 6
    print space, splen
    add esi, 1
    pop ecx
    loop display_loop

    print newline, nlen

    print msg2, slen
    mov eax, [sum]
    
    mov ecx, dispbuf
    add ecx, 5
    mov byte [ecx], 0
    mov ebx, 10
convert_sum:
    dec ecx
    xor edx, edx
    div ebx
    add dl, '0'
    mov [ecx], dl
    test eax, eax
    jnz convert_sum
    
    print ecx, 6
    print newline, nlen

    mov eax, 1
    mov ebx, 0
    int 80h
