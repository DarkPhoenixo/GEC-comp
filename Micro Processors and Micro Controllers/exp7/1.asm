
%macro writenumber 2 
    mov ecx, %1   
    mov edx, %2   
    mov ebx, 1
    mov eax, 4  
    int 80h    
%endmacro 
 
%macro readnumber 2 
    mov eax, 3   
    mov ebx, 0     
    mov ecx, %1   
    mov edx, %2   
    int 80h    
%endmacro 
 
section .data 
    msg db "Enter n", 10
    len equ $ - msg 
     
    msg1 db "Enter 1st number", 10
    len1 equ $ - msg1 
     
    msg2 db "Enter 2nd number",10
    len2 equ $ - msg2 

    sumMsg db "THE SUM IS ",10
    sumLen equ $ - sumMsg


    newline db 10  
 
section .bss    
    sum resb 100 
    number resb 100 
    number2 resb 100 
    nodig resb 2 
     
section .text 
    global _start 
_start: 
    writenumber msg,len 
    readnumber nodig,2 
 
    writenumber msg1,len1      
    readnumber number,100 
 
    writenumber msg2,len2 
    readnumber number2,100 
 
    movzx ecx,byte[nodig] 
    sub ecx,'0' 
    mov esi,ecx 
    dec esi 
 
call add 
writenumber sumMsg,sumLen
writenumber sum,100 
writenumber newline,1    
mov eax, exit 
xor ebx, ebx 
int 80h 
     
add: 
   mov al,[number+esi] 
   mov bl,[number2+esi] 
   adc al,bl 
   aaa 
   pushf 
   or al,30h 
   popf 
   
    
   mov[sum+esi],al 
   dec esi 
   loop add 
ret