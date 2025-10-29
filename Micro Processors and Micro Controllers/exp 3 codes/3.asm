section .data
msg db ' ',10
msgLen equ $-msg
msg1 db 'Length: '
msg1Len equ $-msg1
msg2 db 'Breadth: '
msg2Len equ $-msg2
msg3 db 'Area of rectangle: '
msg3Len equ $-msg3
msg4 db 'Perimeter of rectangle: '
msg4Len equ $-msg4
msg5 db 'Height of trianle: '
msg5Len equ $-msg5
msg6 db 'Base of triangle: '
msg6Len equ $-msg6
msg7 db 'Area of triangle: '
msg7Len equ $-msg7
msg8 db 'Perimeter of triangle: '
msg8Len equ $-msg8
msg9 db 'side1: '
msg9Len equ $-msg9
msg10 db 'side2: '
msg10Len equ $-msg10

%macro writesystem 2
mov eax,4
mov ebx,1
mov ecx, %1
mov edx, %2
int 80h
%endmacro

%macro readsystem 2
mov eax,3
mov ebx,2
mov ecx,%1
mov edx,%2
int 80h
%endmacro

%macro AreaRect 2
mov eax, [length]
sub eax, '0'
mov ebx, [breadth]
sub ebx, '0'
mul ebx
add eax, '0'
mov [areaRect], eax
%endmacro

%macro PeriRect 2
mov eax, [length]
sub eax, '0'
mov ebx, [breadth]
sub ebx, '0'
add eax,ebx
add eax,eax
add eax, '0'
mov [periRect], eax
%endmacro

%macro AreaTri 2
mov al, [height]
sub al, '0'
mov bl, [base]
sub bl, '0'
mul bl
mov bl,0x2
div bl
add al, '0'
mov [areaTri], al
%endmacro

%macro PeriTri 3
mov eax, [side1]
sub eax, '0'
mov ebx, [side2]
sub ebx, '0'
add eax,ebx
mov ebx,[base]
sub ebx, '0'
add eax,ebx
add eax, '0'
mov [periTri], eax
%endmacro

section .bss
length RESB 8
breadth RESB 8
areaRect RESB 8
periRect RESB 8
areaTri RESB 8
periTri RESB 8
height RESB 8
base RESB 8
side1 RESB 8
side2 RESB 8

section .text
global _start
_start:

writesystem msg1,msg1Len
readsystem length,8
writesystem msg2,msg2Len
readsystem breadth,8
AreaRect length,breadth
writesystem msg3,msg3Len
writesystem areaRect,1
writesystem msg, msgLen
PeriRect length,breadth
writesystem msg4,msg4Len
writesystem periRect,1
writesystem msg, msgLen


writesystem msg5,msg5Len
readsystem height,8
writesystem msg6,msg6Len
readsystem base,8
writesystem msg9,msg9Len
readsystem side1,8
writesystem msg10,msg10Len
readsystem side2,8
AreaTri height,base
writesystem msg7,msg7Len
writesystem areaTri,1
writesystem msg, msgLen
PeriTri side1,side2,base
writesystem msg8,msg8Len
writesystem periTri,1
writesystem msg, msgLen

mov eax, 1
mov ebx, 0
int 80h 
