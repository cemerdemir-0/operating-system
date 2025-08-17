#include "os.h"

#define KBD_BUF_SIZE 128
static char kbd_buffer[KBD_BUF_SIZE];
static int buf_head = 0, buf_tail = 0;

static const char keymap[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\','z',
    'x','c','v','b','n','m',',','.','/',0,'*',0,' ',
};

static inline unsigned char inb(unsigned short port) {
    unsigned char ret;
    __asm__ volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void keyboard_handler() {
    unsigned char scancode = inb(0x60);

    if (!(scancode & 0x80)) {
        char c = keymap[scancode];
        if (c) {
            int next = (buf_head + 1) % KBD_BUF_SIZE;
            if (next != buf_tail) {
                kbd_buffer[buf_head] = c;
                buf_head = next;
            }
        }
    }

    outb(0x20, 0x20); // PIC'e EOI
}

// kernel'in çağıracağı fonksiyon
char kbd_getchar() {
    if (buf_head == buf_tail) return 0; // boş
    char c = kbd_buffer[buf_tail];
    buf_tail = (buf_tail + 1) % KBD_BUF_SIZE;
    return c;
}
