SECTION .data
    msg1 db 'Enter the number of elements in array: '
    msg1len equ $-msg1

    msg2 db 'Enter the elements: '
    msg2len equ $-msg2

    msg3 db 'Enter the number to be searched: '
    msg3len equ $-msg3

    msg4 db 'Number found at Index '
    msg4len equ $-msg4

    msg5 db 'Number not found in array'
    msg5len equ $-msg5

    msgIter db 'Iteration ', 0
    msgLow db 'Low: ', 0
    msgMid db 'Mid: ', 0
    msgHigh db 'High: ', 0

    newline db 10
    n1 equ $-newline

%macro writeSys 2
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    int 80h
%endmacro

%macro readSys 2
    mov eax, 3
    mov ebx, 2
    mov ecx, %1
    mov edx, %2
    int 80h
    mov eax, 3
    mov ebx, 2
    mov ecx, trash
    mov edx, 1
    int 80h
%endmacro

SECTION .bss
    num resb 1
    arr resb 10
    s resb 1
    i resb 1
    low resb 1
    mid resb 1
    high resb 1
    trash resb 1
    charBuffer resb 1
    iterations resb 1

SECTION .text
    GLOBAL _start

_start:
    writeSys msg1, msg1len
    readSys num, 1
    sub byte [num], '0'

    writeSys msg2, msg2len
    mov eax, arr
    movzx edx, byte [num]
    call input
    writeSys newline, n1

    writeSys msg3, msg3len
    readSys s, 1
    sub byte [s], '0'         ; Convert ASCII to number
    movzx edi, byte [s]
    mov eax, arr
    movzx edx, byte [num]
    call binarySearch

    mov eax, 1
    xor ebx, ebx
    int 80h

input:
    mov ecx, 0
iLoop:
    cmp ecx, edx
    jge inputDone
    mov esi, eax
    add esi, ecx
    pushad
    readSys esi, 1
    popad
    inc ecx
    jmp iLoop
inputDone:
    ret

binarySearch:
    mov byte [iterations], 0
    mov byte [low], 0
    mov [high], dl

bsLoop:
    ; Exit if low > high
    movzx ecx, byte [low]
    movzx edx, byte [high]
    cmp ecx, edx
    jg notFound

    ; Calculate mid = (low + high) / 2
    pushad
    mov al, [low]
    add al, [high]
    cbw
    mov bl, 2
    div bl
    mov [mid], al
    popad

    ; Print Iteration, Low, Mid, High
    inc byte [iterations]
    pushad
        writeSys msgIter, 9
        mov al, [iterations]
        add al, '0'
        mov [charBuffer], al
        writeSys charBuffer, 1
        writeSys newline, n1

        writeSys msgLow, 5
        mov al, [low]
        add al, '0'
        mov [charBuffer], al
        writeSys charBuffer, 1
        writeSys newline, n1

        writeSys msgMid, 5
        mov al, [mid]
        add al, '0'
        mov [charBuffer], al
        writeSys charBuffer, 1
        writeSys newline, n1

        writeSys msgHigh, 6
        mov al, [high]
        add al, '0'
        mov [charBuffer], al
        writeSys charBuffer, 1
        writeSys newline, n1

        writeSys newline, n1
    popad

    ; Load mid value and compare
    movzx edx, byte [mid]
    movzx esi, byte [eax + edx]
    sub esi, '0'           ; Convert ASCII to number
    cmp edi, esi
    je found
    jl goLeft

    ; Go right
    mov bl, [mid]
    inc bl
    mov [low], bl
    jmp bsLoop

goLeft:
    mov bl, [mid]
    dec bl
    mov [high], bl
    jmp bsLoop

found:
    add edx, '0'
    mov [i], dl
    pushad
    writeSys msg4, msg4len
    writeSys i, 1
    writeSys newline, n1
    popad
    ret

notFound:
    writeSys msg5, msg5len
    writeSys newline, n1
    ret
