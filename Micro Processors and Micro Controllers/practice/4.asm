
section.data 
msg db "Enter the first number: ", 10
msglen equ $-msg
msg1 db "Enter the second number: ", 10
msglen1 equ $-msg1
msg2 db "THe sum of numbers is: ", 10
msglen2 equ $-msg2
msg3 db "The difference of the numbers: ", 10
msglen3 equ $-msg3
msg4 db "The product of the numbers: ", 10
msglen4 equ $-msg4
msg5 db "The quotient of num/num2: ", 10
msglen5 equ $-msg5
msg6 db "The remainder of the number is : ", 10
msglen6 equ $-msg6


%macro write 2 
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

%macro add 2 
mov eax,[num1]
mov ebx,[num2]
add eax, ebx
mov [sum], eax
int 80h
%endmacro

%macro sub 2 
mov eax,[num1]
mov ebx,[num2]
sub eax, ebx
mov [diff], eax
int 80h
%endmacro

%macro mult 2
    mov eax,[num1]
    mov ebx,[num2]
    mul ebx
    mov [prod], eax
    int 80h
%endmacro


%macro div 2
    mov al,[num1]
    mov bl,[num2]
    xor ah, ah
    div bl
    mov [quot], al
    mov [rem], ah
    int 80h
%endmacro

section.bss
num1 resb 5
num2 resb 5
sum resb 5
diff resb 5
prod resb 5
quot resb 5
rem resb 5 

section.text
write msg,msglen
read num1,5
write msg1,msglen1
read num2,5

