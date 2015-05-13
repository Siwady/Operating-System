all: floppya.img test/syscall-test.bin

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
	dd if=/dev/zero of=floppya.img bs=512 count=2880
	dd if=bootload.bin of=floppya.img bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=floppya.img bs=512 seek=3 conv=notrunc
	dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=test/syscall-test.bin of=floppya.img bs=512 count=1 seek=11 conv=notrunc
	
clean :
	rm -f *.o
	rm -f *.bin
	rm -f test/*.o
	
	

test/test.o: test/test.c
	bcc -ansi -c -o $@ $<
	
test/os.o: test/os.asm
	as86 $< -o $@
	
test/start.o: test/start.asm
	as86 $< -o $@
	
test/syscall-test.bin: test/start.o  test/test.o test/os.o 
	ld86 -o $@ -d $^