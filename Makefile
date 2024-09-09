# $^ - substituted with all of target dependencies
# $< - first dependancy
# $@ - target file

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c user/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h user/*.h)
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o kernel/paging_init.o}

CC = /usr/bin/i686-linux-gnu-gcc
GDB = /usr/bin/gdb-multiarch
# -g debugging flag
CFLAGS = -g


os-image: boot/32bit_boot.bin kernel.bin
	cat $^ > os-image		

kernel.bin : boot/kernel_entry.o ${OBJ}
	i686-linux-gnu-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf : boot/kernel_entry.o ${OBJ}
	i686-linux-gnu-ld -o $@ -Ttext 0x1000 $^ 

run: os-image
	qemu-system-i386 -fda os-image

debug: os-image kernel.elf
	qemu-system-i386 -s -fda os-image &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# generic compiles

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -fno-pie -ffreestanding -c $< -o $@

%.o:   %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@


clean:
	rm -rf *.bin *.o *.dis *.map *.elf
