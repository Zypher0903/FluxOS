#include "../include/common.h"

void pit_init(u32 freq) {
    u32 div = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, div >> 8);
}
