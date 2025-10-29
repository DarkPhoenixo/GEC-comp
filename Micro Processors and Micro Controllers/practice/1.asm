section.data
msg db "Hello",10
msglen equ $-msg

section.text 

global _start
mov eax , 4          
mov ebx , 1           
mov ecx , msg
mov edx , msglen
mov ebx, 0        
mov eax, 1           
int 80h