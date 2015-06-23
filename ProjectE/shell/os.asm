.global _syscall_printString
.global _syscall_printStringColor
.global _syscall_readString
.global _syscall_readStringColor
.global _syscall_readSector
.global _syscall_moveCursor
.global _syscall_readFile
.global _syscall_Clr
.global _syscall_executeProgram
.global _syscall_nextLine
.global _syscall_terminate
.global _syscall_putInMemory
.global _syscall_printCharColor
.global _syscall_writeSector
.global _syscall_deleteFile
.global _syscall_writeFile
.global _syscall_getBufferSize
.global _syscall_printInt


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
	
_syscall_readFile:
	push bp
	mov bp,sp
	mov ax,#6
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
	
_syscall_Clr:
	mov ax,#7
	int #0x21
	ret
	
;syscall_executeProgram(char filename[], int segment)
_syscall_executeProgram:
	push bp
	mov bp,sp
	mov ax,#8
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret
	
_syscall_nextLine:
	mov ax,#9
	int #0x21
	ret
	
_syscall_terminate:
	mov ax,#10
	int #0x21
	ret
	
_syscall_putInMemory:
	push bp
	mov bp,sp
	mov ax,#11
	mov bx,[bp+4]
	mov cx,[bp+6]
	mov dx,[bp+8]
	int #0x21
	pop bp
	ret
	
_syscall_printCharColor:
	push bp
	mov bp,sp
	mov ax,#12
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret

_syscall_writeSector:
	push bp
	mov bp,sp
	mov ax,#13
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret

_syscall_deleteFile:
	push bp
	mov bp,sp
	mov ax,#14
	mov bx,[bp+4]
	int #0x21
	pop bp
	ret
	
_syscall_writeFile:
	push bp
	mov bp,sp
	mov ax,#15
	mov bx,[bp+4]
	mov cx,[bp+6]
	mov dx,[bp+8]
	int #0x21
	pop bp
	ret

_syscall_getBufferSize:
	push bp
	mov bp,sp
	mov ax,#16
	mov bx,[bp+4]
	int #0x21
	pop bp
	ret

_syscall_printInt:
	push bp
	mov bp,sp
	mov ax,#17
	mov bx,[bp+4]
	mov cx,[bp+6]
	int #0x21
	pop bp
	ret


