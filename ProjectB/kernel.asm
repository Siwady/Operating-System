;kernel.asm
;Michael Black, 2007

;kernel.asm contains assembly functions that you can use in your kernel

	.global _putInMemory
	.global _makeInterrupt21
	.global _printChar
	.global _readChar
	.global _moveCursor
	.global _changePage
	.global _readSector
;	.extern _handleInterrupt21

;void putInMemory (int segment, int address, char character)
_putInMemory:
	push bp
	mov bp,sp
	push ds
	mov ax,[bp+4]
	mov si,[bp+6]
	mov cl,[bp+8]
	mov ds,ax
	mov [si],cl
	pop ds
	pop bp
	ret

;void printChar(char character)
_printChar:
	push bp
	mov bp,sp
	mov al, [bp+4]
	mov ah, #0x0e
	int #0x10
	pop bp
	ret
	
;char readChar()
_readChar:
	push bp
	mov ah, #0
	int #0x16
	pop bp
	ret

;void moveCursor(int column,int row,int page)
_moveCursor:
	push bp
	mov bp,sp
	mov bh,[bp+8]  ;page
	mov cl,[bp+6]    ;row
	mov ch,[bp+4]   ;column
	mov ah,#0x2
	mov dh,cl
	mov dl,ch
	int #0x10
	pop bp
	ret

;void changePage(int page)
_changePage:
	push bp
	mov bp,sp
	mov ah, #0x5
	mov al,[bp+4]   ;page
	int #0x10
	pop bp
	ret
	
;void readSector(char* buffer,int sector)
_readSector:
	push bp
	mov bp,sp
	
	sub sp,#6
	mov bx,[bp+4]   ;buffer
	mov ax,[bp+6]
;--------------------------------------------	
	mov cl,#36
	div cl
	xor ah,ah
	mov [bp-2],ax  ;Track
	
;--------------------------------------------	
	mov ax,[bp+6]
	mov cl,#18
	div cl
	and al,#0x1
	xor dx,dx
	mov dl,al
	mov [bp-4],dx   ;head
;---------------------------------------------
	add ah,#1
	xor dx,dx
	mov dl,ah
	mov [bp-6], dx  ;relative sector 
	
	mov ah, #0x2 
	mov al,#0x1      ;number of sectors to read

	mov ch,[bp-2]  ;set Track
	mov cl, [bp-6]  ;set Relative sector
	mov dh,[bp-4]  ; set Head
	mov dl, #0x0    ;device number
	int #0x13
	add sp,#6
	pop bp
	ret
	
	
	
	
;void makeInterrupt21()
;this sets up the interrupt 0x21 vector
;when an interrupt 0x21 is called in the future, 
;_interrupt21ServiceRoutine will run

_makeInterrupt21:
	;get the address of the service routine
	mov dx,#_interrupt21ServiceRoutine
	push ds
	mov ax, #0	;interrupts are in lowest memory
	mov ds,ax
	mov si,#0x84	;interrupt 0x21 vector (21 * 4 = 84)
	mov ax,cs	;have interrupt go to the current segment
	mov [si+2],ax
	mov [si],dx	;set up our vector
	pop ds
	ret

;this is called when interrupt 21 happens
;it will call your function:
;void handleInterrupt21 (int AX, int BX, int CX, int DX)
_interrupt21ServiceRoutine:
;	push dx
;	push cx
;	push bx
;	push ax
;	call _handleInterrupt21
;	pop ax
;	pop bx
;	pop cx
;	pop dx

;	iret
