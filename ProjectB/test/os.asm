.global _syscall_printString
.global _syscall_printStringColor
.global _syscall_readString
.global _syscall_readStringColor
.global _syscall_readSector
.global _syscall_moveCursor

_syscall_printString:
	push bp
	mov bp,sp
	mov ax,#0
	mov bx,[bp+4]
	int #0x21
	pop bp
	ret
	
_syscall_printStringColor:
	push bp
	mov bp,sp
	mov ax,#4
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret
	
	
_syscall_readString:
	push bp
	mov bp,sp
	mov ax,#1
	mov bx,[bp+4]
	int #0x21
	pop bp
	ret
	
_syscall_readStringColor:
	push bp
	mov bp,sp
	mov ax,#3
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret
	
_syscall_readSector:
	push bp
	mov bp,sp
	mov ax,#2
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret
	
_syscall_moveCursor:
	push bp
	mov bp,sp
	mov ax,#5
	mov bx,[bp+4]
	mov cx,[bp+6]
	mov dx,[bp+8]
	int #0x21
	pop bp
	ret
	
