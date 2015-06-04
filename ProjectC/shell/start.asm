;start.asm


.extern _main
.extern _syscall_terminate

entry start

start:
	call _main
	call _syscall_terminate 
loop1:  jmp loop1
