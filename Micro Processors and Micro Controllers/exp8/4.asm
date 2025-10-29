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
    msg db 'Enter the elements of the array : ', 0xA
    plen equ $ - msg
    msg1 db 'Count of elements less than 5: '
    mlen equ $ - msg1
    msg2 db 'Count of elements greater than 5: '
    m2len equ $ - msg2
    msg3 db 'Count of elements equal to 5: '
    m3len equ $ - msg3
    newline db 0xA
    nlen equ $ - newline

section .bss
    array resb 5
    num resb 2
    countLess resb 1
    countGreater resb 1
    countEqual resb 1

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
    read num, 2
    mov al, [num]
    sub al, '0'   
    mov [array + esi], al
    inc esi
    pop ecx
    loop input_loop

    mov ecx, 5
    mov esi, 0
    mov byte[countLess], 0
    mov byte[countGreater], 0
    mov byte[countEqual], 0
    
count_loop:
    mov al, [array + esi]
    cmp al, 5
    je equal_to_5
    jg greater_than_5
    inc byte[countLess]
    jmp continue_count
greater_than_5:
    inc byte[countGreater]
    jmp continue_count
equal_to_5:
    inc byte[countEqual]
continue_count:
    inc esi
    loop count_loop

    print msg1, mlen
    mov al, [countLess]
    add al, '0'
    mov [num], al
    print num, 1
    print newline, nlen

    print msg2, m2len
    mov al, [countGreater]
    add al, '0'
    mov [num], al
    print num, 1
    print newline, nlen

    print msg3, m3len
    mov al, [countEqual]
    add al, '0'
    mov [num], al
    print num, 1
    print newline, nlen

    mov eax, 1
    mov ebx, 0
    int 80h
