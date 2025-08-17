#include "os.h"
#include <stdint.h>
#define VGA_MEM ((volatile uint16_t*)0xB8000)
#define COL 80
#define WHITE_ON_BLACK 0x0F
#define VGA_ADDR 0xB8000
static size_t cursor = 0;

void vga_clear(void){
    for(size_t i=0;i<COL*25;i++) VGA_MEM[i] = (WHITE_ON_BLACK<<8) | ' ';
    cursor = 0;
}
void putc(char c){
    if(c=='\n'){ cursor = (cursor/COL + 1)*COL; return; }
    VGA_MEM[cursor++] = ((uint16_t)WHITE_ON_BLACK<<8) | (uint8_t)c;
}
void print(const char* s){ while(*s) putc(*s++); }

void print_uint(uint64_t n){
    char b[21]; int i=20; b[i--]='\0';
    if(!n) b[i--]='0';
    while(n){ b[i--]='0'+(n%10); n/=10; }
    print(&b[i+1]);
}
void print_hex16(uint16_t x){
    const char* h="0123456789ABCDEF";
    putc('0'); putc('x');
    for(int i=12;i>=0;i-=4) putc(h[(x>>i)&0xF]);
}

static uint16_t* vga = (uint16_t*)VGA_ADDR;

void yazdir(const char* s) {
    while (*s) {
        vga[cursor++] = (WHITE_ON_BLACK << 8) | *s++;
    }
}

void itoa(uint32_t n, char* str) {
    int i = 0;
    char tmp[16];
    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }
    while (n > 0) {
        tmp[i++] = '0' + (n % 10);
        n /= 10;
    }
    for (int j = 0; j < i; j++) {
        str[j] = tmp[i - j - 1];
    }
    str[i] = '\0';
}

void print_char(char c) {
    vga[cursor++] = (WHITE_ON_BLACK << 8) | c;
}

