INCLUDEDIR=include
VPATH=kernel:boot:lib:drivers:mm:dev:init
CC=gcc
AS=nasm
CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -I$(INCLUDEDIR) -c
LDFLAGS=-Tlink.ld -m elf_i386 -o ../bin/aspidistra
ASFLAGS=-felf

all: stdconv.o gdt.o idt.o descriptor_tables.o interrupts.o head.o main.o console.o keyboard.o cpu.o cpuid.o mem.o io.o timer.o string.o paging.o common.o stdio.o liz.o
	ld $(LDFLAGS) head.o main.o gdt.o idt.o descriptor_tables.o interrupts.o mem.o cpu.o cpuid.o console.o timer.o io.o string.o paging.o common.o stdio.o keyboard.o liz.o stdconv.o

%.o: %.s %.c

%.c: 
	$(CC) $(CFLAGS) $<

%.s: 
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm *.o
