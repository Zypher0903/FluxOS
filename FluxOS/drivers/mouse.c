static int mx = 160, my = 100;
static u8 mouse_cycle = 0;
static s8 packet[3];

void mouse_handler() {
    u8 status = inb(0x64);
    if (!(status & 0x20)) return;

    packet[mouse_cycle++] = inb(0x60);
    if (mouse_cycle == 3) {
        mx += packet[1];
        my -= packet[2];
        if (mx < 0) mx = 0;
        if (mx > 319) mx = 319;
        if (my < 0) my = 0;
        if (my > 199) my = 199;

        if (packet[0] & 1) wm_handle_click(mx, my, 1);
        if (!(packet[0] &1)) wm_handle_click(mx, my, 0);

        wm_draw_mouse(mx, my);
        mouse_cycle = 0;
    }
    outb(0xA0, 0x20);
    outb(0x20, 0x20);
}