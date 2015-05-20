
CFLAGS = -g -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`

all: bin/sfs

clean:
	rm -rf bin obj

bin: 
	mkdir -p bin

bin/sfs: bin obj/sfs.o obj/device.o obj/main.o
	g++ obj/* -o bin/sfs $(LINKFLAGS)

obj:
	mkdir -p obj

obj/main.o: obj main.c sfs.h
	gcc -g $(CFLAGS) -c main.c -o $@

obj/sfs.o: obj sfs.c sfs.h 
	g++ -g $(CFLAGS) -c sfs.c -o $@

obj/device.o: obj device.c device.h
	g++ -g $(CFLAGS) -c device.c -o $@

floppya.img: bootload.bin kernel.bin
	dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
	dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc

