section .data
    prompt db 'Enter a number: '
    prompt_len equ $ - prompt
    msg db 'Factorial: '
    msg_len equ $ - msg
    newline db 10

section .bss
    num resb 2
    result resb 1

section .text
global _start

write_proc:
    push ebp
    mov ebp, esp
    mov eax, 4
    mov ebx, 1
    mov ecx, [ebp+12]
    mov edx, [ebp+8]
    int 80h
    mov esp, ebp
    pop ebp
    ret 8

read_proc:
    push ebp
    mov ebp, esp
    mov eax, 3
    mov ebx, 0
    mov ecx, [ebp+12]
    mov edx, [ebp+8]
    int 80h
    mov esp, ebp
    pop ebp
    ret 8

_start:
    push prompt
    push prompt_len
    call write_proc

    push num
    push 2
    call read_proc

    push msg
    push msg_len
    call write_proc

  
    movzx eax, byte [num]
    sub al, '0'
   
    mov ebx, eax   
    dec ebx        
    
factorial_loop:
    test ebx, ebx  
    jz done        
    mul ebx        
    dec ebx         
    jmp factorial_loop

done:
   
    add al, '0'
    mov [result], al
    
   
    push result
    push 1
    call write_proc

  
    push newline
    push 1
    call write_proc

 
    mov eax, 1
    mov ebx, 0
    int 80h