section .data
msg1 db "Enter the number of elements in the fibonacci series ",10
msglen equ $-msg1
msg2 db "The fibonacci series is: ",10
msg2len equ $-msg2


%macro print 2
    push ebx
    push ecx
    push edx
    push eax
    mov eax, 4
    mov ebx, 1
    mov ecx, %1
    mov edx, %2
    pop eax
    pop edx
    pop ecx
    pop ebx
    int 80h
%endmacro

%macro read 2
    push ebx
    push ecx
    push edx
    push eax
    mov eax, 3
    mov ebx, 0
    mov ecx, %1
    mov edx, %2
    pop eax
    pop edx
    pop ecx
    pop ebx
    int 80h
%endmacro

%macro add 2
    push ebx
    push ecx
    push edx
    push eax

    mov eax, %1
    sub eax, '0'
    mov ebx, %2
    sub ebx, '0'
    add eax, ebx
    add eax, '0'
    mov [sum], eax
    pop eax
    pop edx
    pop ecx
    pop ebx
    int 80h
    
    

section .bss
num resb 5
fib1 resb 5
fib2 resb 5
sum resb 5

section .text
mov eax, 1
mov ebx, 0

global _start
_start:
    print msg1, msglen
    read num, 5

  mov byte[fib1], 0
    mov byte[fib2], 0
    
    movzx ecx,byte[num]

    fib :
  push ecx
    print msg2, msg2len
    print fib1, 5
    add fib1, fib2
    mov [fib1], [fib2]
    mov [fib2], sum 
    pop ecx
    loop fib

    mov eax, 1
    mov ebx, 0
    int 80h
    

