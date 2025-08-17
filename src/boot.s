.set MAGIC, 0x1BADB002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.global _start
.extern kernel_main
_start:
    # GRUB bize (eax=magic, ebx=multiboot_info*) veriyor

    push %ebx        # 2. argüman: multiboot_info pointer
    push %eax        # 1. argüman: magic number
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
