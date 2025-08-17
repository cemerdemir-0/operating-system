#include <stdint.h>
#include "os.h"

uint32_t tick = 0;

void timer_callback() {
    tick++;
}

void timer_install() {
    int hz = 100;
    int divisor = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}
