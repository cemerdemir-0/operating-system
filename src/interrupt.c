#include "os.h"

extern void isr1(); // klavye IRQ1

void isr_install() {
    idt_set_gate(0x21, (uint32_t)isr1, 0x08, 0x8E);
}
