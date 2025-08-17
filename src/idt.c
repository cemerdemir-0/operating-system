#include "os.h"

struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void idt_load(uint32_t);

static struct idt_entry idt[256];
struct idt_ptr   idtp;   // static’i kaldır

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel     = sel;
    idt[num].always0 = 0;
    idt[num].flags   = flags;
}


static inline void pic_remap() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);   // maskeyi kaldır (IRQ0–7 açık)
    outb(0xA1, 0x0);   // maskeyi kaldır (IRQ8–15 açık)
}

void idt_install() {
    idtp.limit = (sizeof(struct IDTEntry) * 256) - 1;
    idtp.base  = (uint32_t)&idt;
    for (int i=0; i<256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    idt_load();
    pic_remap();   // 🔴 BURADA PIC'i açıyoruz
}
