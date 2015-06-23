all: floppya.img shell/shell.bin

run: all
	- bochs -f opsys.bxrc 

kernel.bin: start.o kernel.o kernel_asm.o 
	ld86 -o $@ -d $^

kernel.o: kernel.c
	bcc -ansi -c -o $@ $<

kernel_asm.o: kernel.asm
	as86 $< -o $@

start.o: start.asm
	as86 $< -o $@


bootload.bin: bootload.asm
	nasm $< -f bin -o $@

floppya.img: bootload.bin kernel.bin
	dd if=bootload.bin of=floppya.img bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=floppya.img bs=512 seek=3 conv=notrunc
	dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=shell/shell.bin of=floppya.img bs=512 count=1 seek=11 conv=notrunc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f shell/*.o

shell/shell.o: shell/shell.c
	bcc -ansi -c -o $@ $<
	
shell/os.o: shell/os.asm
	as86 $< -o $@
	
shell/start.o: shell/start.asm
	as86 $< -o $@
	
shell/shell.bin: shell/start.o  shell/shell.o shell/os.o 
	ld86 -o $@ -d $^
	
