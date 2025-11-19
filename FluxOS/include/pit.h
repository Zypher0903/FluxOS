u32 tick = 0;
void timer_handler() {
    tick++;
    scheduler_tick();
    outb(0x20, 0x20);
}

void pit_init(u32 freq) {
    u32 divisor = 1193180 / freq;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}
