#pragma once
#include <stdint.h>
#include <stddef.h>

/* vga.c */
void vga_clear(void);
void putc(char c);
void print(const char* s);
void print_hex16(uint16_t x);
void print_uint(uint64_t x);

/* cpuid.c */
void cpu_brand(char out[49]);

/* pci.c */
void pci_scan_and_print(void);

void yazdir(const char* s);

void itoa(uint32_t n, char* str);

char getch();

void print_char(char c);

int strcmp(const char* s1, const char* s2);

void idt_install();
void isr_install();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);

char kbd_getchar();

extern struct idt_ptr idtp;
