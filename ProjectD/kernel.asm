;kernel.asm
;Michael Black, 2007
;Edward Siwady,2015

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
	.extern _printStringColor
	.extern _readString
	.extern _readStringColor
	.extern _readFile
	.extern _executeProgram
	.extern _pressReturn
	.extern _terminate
	.extern _deleteFile
	.extern _writeFile
	.extern _getBufferSize
	.extern _printInt
	.global _interrupt21ServiceRoutine
	.global _execute_readString
	.global _execute_readStringColor
	.global _execute_printString
	.global _execute_printStringColor
	.global _execute_readSector
	.global _execute_moveCursor
	.global _execute_readFile
	.global _execute_Clr
	.global _execute_executeProgram
	.global _execute_pressReturn
	.global _execute_terminate
	.global _execute_putInMemory
	.global _execute_printCharColor
	.global _execute_writeSector
	.global _execute_deleteFile
	.global _execute_writeFile
	.global _execute_getBufferSize
	.global _execute_printInt
	.global _loadProgram
	.global _changeBackgroundColor
	.global _Clr
	.global _getCursorColumn
	.global _getCursorRow
	.global _moveCursorUp
	.global _moveCursorDown
	.global _ScrollDown
	.global _putInSegment
	.global _launchProgram
	.global _nextLine
	.global _writeSector
	
;	.extern _handleInterrupt21


;void nextLine(int page)
_nextLine:
	push bp
	mov bp,sp
	mov al, #10
	mov ah, #0x0e
	mov bl,#0xA
	int #0x10
	
	mov ah,#0x3
	mov bh,[bp+4] ;  page
	int #0x10
;---------------------------------------------------------	
	;set cursor position
	mov dl,#0
	mov ah,#0x2
	int #0x10
	
	pop bp
	ret


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

;void putInSegment(char buffer[],int segment,int size);
_putInSegment:
	push bp
	mov bp,sp
	mov si,[bp+4]
	mov es,[bp+6]
	mov di, #0
	mov cx,[bp+8]
	rep 
	movsb
	pop bp
	ret
	

; void launchProgram(int segment);
_launchProgram:
	mov bp,sp
	mov bx, [bp+2]
	
	mov ds, bx
	mov ss, bx
	mov es, bx
	mov ax,#0xfff0
	mov bp,ax
	mov sp,ax
	
	push bx
	push #0
	
	; Switch to program
	retf
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


;printCharC(char cha, int Color)
_printCharC:
	push bp
	mov bp,sp
	mov ah,#9 
	mov al,[bp+4]   ;Char
	mov bh,#0        ;Page
	mov bl,[bp+6]    ;Color   (87 is blinking  ,   0xA  is Green)
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
	

;getCursorColumn()
_getCursorColumn:
	mov ah,#0x3
	mov bh,#0  ;  page
	int #0x10
	xor ax,ax
	mov al,dl
	ret
	
;getCursorRow()
_getCursorRow:
	mov ah,#0x3
	mov bh,#0  ;  page
	int #0x10
	xor ax,ax
	mov al,dh
	ret


;moveCursorUp()
_moveCursorUp:
	;get cursor position
	mov ah,#0x3
	mov bh,#0  ;  page
	int #0x10
;---------------------------------------------------------	
	;set cursor position
	sub dh,#1
	mov dl,#80
	mov ah,#0x2
	int #0x10
	ret
	
;moveCursorDown()
_moveCursorDown:
	;get cursor position
	mov ah,#0x3
	mov bh,#0  ;  page
	int #0x10
;---------------------------------------------------------	
	;set cursor position
	add dh,#1
	mov dl,#0
	mov ah,#0x2
	int #0x10
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
	

;void readSector(char* buffer,int sector)
_writeSector:
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
	
	mov ah, #0x3 
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
	jne try_readString
	mov ax, #_execute_printString
	jmp ax
try_readString:
	cmp ax,#1
	jne try_readSector
	mov ax,#_execute_readString
	jmp ax
try_readSector:
	cmp ax,#2
	jne try_readStringColor
	mov ax,#_execute_readSector
	jmp ax
try_readStringColor:
	cmp ax,#3
	jne try_printStringColor
	mov ax, #_execute_readStringColor
	jmp ax
try_printStringColor:
	cmp ax,#4
	jne try_moveCursor
	mov ax,#_execute_printStringColor
	jmp ax
try_moveCursor:
	cmp ax,#5
	jne try_readFile
	mov ax,#_execute_moveCursor
	jmp ax
try_readFile:	
	cmp ax,#6
	jne try_Clr
	mov ax,#_execute_readFile
	jmp ax
try_Clr:
	cmp ax,#7
	jne try_executeProgram
	mov ax,#_execute_Clr
	jmp ax
try_executeProgram:
	cmp ax,#8
	jne try_pressReturn
	mov ax,#_execute_executeProgram
	jmp ax
try_pressReturn:
	cmp ax,#9
	jne try_terminate
	mov ax,#_execute_pressReturn
	jmp ax
try_terminate:
	cmp ax,#10
	jne try_putInMemory
	mov ax,#_execute_terminate
	jmp ax
try_putInMemory:
	cmp ax,#11
	jne try_printCharColor
	mov ax,#_execute_putInMemory
	jmp ax
try_printCharColor:
	cmp ax,#12
	jne try_writeSector
	mov ax,#_execute_printCharColor
	jmp ax
try_writeSector:
	cmp ax,#13
	jne try_deleteFile
	mov ax,#_execute_writeSector
	jmp ax
try_deleteFile:
	cmp ax,#14
	jne try_writeFile
	mov ax,#_execute_deleteFile
	jmp ax
try_writeFile:
	cmp ax,#15
	jne try_getBufferSize
	mov ax,#_execute_writeFile
	jmp ax
try_getBufferSize:
	cmp ax,#16
	jne try_printInt
	mov ax, #_execute_getBufferSize
	jmp ax
try_printInt:
	cmp ax,#17
	mov ax, #_execute_printInt
	jmp ax
	

_execute_printString:
	push bx
	call _printString 
	add sp,#2
	iret
	
_execute_moveCursor:
	push dx
	push cx
	push bx
	call _moveCursor 
	add sp,#6
	iret

_execute_printStringColor:
	push cx
	push bx
	call _printStringColor 
	add sp,#4
	iret


_execute_readString:
	push bx
	call _readString 
	add sp,#2
	iret
	
_execute_readStringColor:
	push cx
	push bx
	call _readStringColor 
	add sp,#4
	iret
	

_execute_readSector:
	push cx
	push bx
	call _readSector
	add sp,#4
	iret
	
_execute_readFile:
	push cx
	push bx
	call _readFile
	add sp,#4
	iret
	
_execute_Clr:
	call _Clr
	iret
	
_execute_executeProgram:
	push cx
	push bx
	call _executeProgram
	add sp,#4
	iret
	
_execute_pressReturn:
	call _nextLine
	iret
	
_execute_terminate:
	call _terminate
	iret
	
_execute_putInMemory:
	push dx
	push cx
	push bx
	call _putInMemory
	add sp,#6
	iret

_execute_printCharColor:
	push cx
	push bx
	call _printCharC
	add sp,#4
	iret
	
_execute_writeSector:
	push cx
	push bx
	call _writeSector
	add sp,#4
	iret

_execute_deleteFile:
	push bx
	call _deleteFile 
	add sp,#2
	iret
	
_execute_writeFile:
	push dx
	push cx
	push bx
	call _writeFile
	add sp,#6
	iret
	
_execute_getBufferSize:
	push bx
	call _getBufferSize 
	add sp,#2
	iret
	
_execute_printInt:
	push cx
	push bx
	call _printInt
	add sp,#4
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
     
        mov ah,#2       ;move cursor 
        mov bh,#0
        mov dh,#0
        mov dl,#0
        int #0x10

	ret
	
_ScrollDown:
	mov ah,#6
        mov al,#0
        mov bh,#7
        mov cx,#0
	mov cl,#2
        mov dl,#79
        mov dh,#2
        int  #0x10
	ret


