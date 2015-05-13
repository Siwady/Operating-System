;kernel.asm
;Michael Black, 2007

;kernel.asm contains assembly functions that you can use in your kernel

	.global _putInMemory
	.global _makeInterrupt21
	.global _printChar
	.global _readChar
	.global _printCharC
	.global _moveCursor
	.global _changePage
	.global _readSector
	.extern _printString
	.extern _readString
	.global _interrupt21ServiceRoutine
	.global _execute_readString
	.global _execute_printString
	.global _execute_readSector
	.global _end
	.global _loadProgram
	.global _changeBackgroundColor
	.global _Clr
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
	mov bl,#0xA
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


;printCharC(char cha)
_printCharC:
	push bp
	mov bp,sp
	mov ah,#9 
	mov al,[bp+4]   ;Char
	mov bh,#0        ;Page
	mov bl,#0xA    ;Color   (87 is blinking)
	mov cx,#1 
	int #0x10  
;---------------------------------------------------------
	;get cursor position
	mov ah,#0x3
	mov bh,#0  ;  page
	int #0x10
;---------------------------------------------------------	
	;set cursor position
	add dl,#1
	mov ah,#0x2
	int #0x10
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
	cmp ax,#0
	je _execute_printString
	cmp ax,#1
	je _execute_readString
	cmp ax,#2
	je _execute_readSector



_execute_printString:
	push bx
	call _printString 
	add sp,#2
	jmp _end


_execute_readString:
	push bx
	call _readString 
	add sp,#2
	jmp _end
	

_execute_readSector:
	push cx
	push bx
	call _readSector
	add sp,#4
	jmp _end
	
	
	
_end:
	iret
	

_loadProgram:
	mov ax, #0x2000
	mov ds, ax
	mov ss, ax
	mov es, ax
	;let's have the stack start at 0x2000:fff0
	mov ax, #0xfff0
	mov sp, ax
	mov bp, ax   ; Read the program from the floppy
	mov cl, #12  ;cl holds sector number
	mov dh, #0  ;dh holds head number - 0
	mov ch, #0   ;ch holds track number - 0
	mov ah, #2  ;absolute disk read
	mov al, #1   ;read 1 sector
	mov dl, #0   ;read from floppy disk A
	mov bx, #0  ;read into offset 0 (in the segment)
	int #0x13      ;call BIOS disk read function
	
	; Switch to program
	jmp #0x2000:#0
	
;changeBackgroundColor(int color);
_changeBackgroundColor:
	push bp
	mov bp,sp
	mov bh, #0x00
	mov ah, #0x0B
	mov bl,[bp+4]   ;color
	int #0x10
	pop bp
	ret

;putPixel(int color, int page,int x, int y)
_Clr:
	mov ah,#6    ;THIS WILL CLEAR SCREEN
        mov al,#0
        mov bh,#7
        mov cx,#0
        mov dl,#79
        mov dh,#24
        int  #0x10
     
        mov ah,#2       ;THIS WILL CONTROL CURSOR LOCATION
        mov bh,#0
        mov dh,#0
        mov dl,#0
        int #0x10

	ret
	

	



