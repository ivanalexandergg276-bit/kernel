# openKRN - Makefile
# Copyright (C) 2026 Reliable Kernel Corp.

CC = gcc
LD = ld
ASM = nasm

# Flags de compilación para un kernel de 32 bits independiente del sistema operativo anfitrión
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -c
LDFLAGS = -m elf_i386 -T linker.ld
ASMFLAGS = -f elf32

# Archivos objeto que formarán el kernel
OBJS = boot.o kmain.o vga.o

all: openkrn.bin

boot.o: boot.asm
	$(ASM) $(ASMFLAGS) boot.asm -o boot.o

kmain.o: kmain.c
	$(CC) $(CFLAGS) kmain.c -o kmain.o

vga.o: vga.c
	$(CC) $(CFLAGS) vga.c -o vga.o

openkrn.bin: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o openkrn.bin

# Comando para limpiar los archivos compilados temporales
clean:
	rm -rf *.o openkrn.bin

# Comando rápido para probar el kernel directamente en la máquina virtual QEMU
run: openkrn.bin
	qemu-system-i386 -kernel openkrn.bin