section .data
    prompt db "Enter a string: ", 0
    prompt_len equ $ - prompt
    result db "Reversed string: ", 0
    result_len equ $ - result
    newline db 0xa

section .bss
    string resb 100    
    rev_string resb 100 
    strlen resb 1      

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

section .text
    global _start

_start:
    print prompt, prompt_len
    input string, 100
    dec eax         
    mov [strlen], eax
    
    mov ecx, [strlen]    
    mov esi, 0          
    mov edi, ecx        
    dec edi             
    
reverse_loop:
    mov al, [string + esi]    
    mov [rev_string + edi], al 
    inc esi
    dec edi
    loop reverse_loop
    
    print result, result_len
    print rev_string, [strlen]
    print newline, 1
    
    mov eax, 1
    mov ebx, 0
    int 0x80
