void keyboard_handler() {
    u8 sc = inb(0x60);
    if (sc & 0x80) return;
    if (sc == 0x1C) wm_handle_key('\n');
    else if (sc < 0x80) wm_handle_key(sc);  // proširi sa mapom
    outb(0x20, 0x20);
}
