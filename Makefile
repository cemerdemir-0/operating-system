TARGET   := kernel.bin
ISO      := os.iso
CC       := gcc
LD       := ld
CFLAGS   := -m32 -ffreestanding -fno-pic -fno-stack-protector -nostdlib -O2 -Wall -Wextra
LDFLAGS  := -m elf_i386 -T linker.ld

# Burada sadece senin var olan dosyaların var
SRCS := src/boot.s src/kernel.c src/vga.c src/cpuid.c src/pci.c src/keyboard.c src/string.c src/idt.c src/interrupt.c src/isr.s
OBJS := $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)
OBJS := $(OBJS:.asm=.o)


.PHONY: all run clean iso

all: $(TARGET) iso

$(TARGET): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

iso: $(TARGET) iso/boot/grub/grub.cfg
	mkdir -p iso/boot
	cp $(TARGET) iso/boot/
	grub-mkrescue -o $(ISO) iso

run: all
	qemu-system-i386 -cdrom $(ISO) -m 2048

clean:
	rm -f $(TARGET) $(OBJS) $(ISO)
	rm -rf iso/boot/kernel.bin
