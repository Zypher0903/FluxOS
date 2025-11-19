#include "../include/common.h"
#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/pit.h"
#include "../include/wm.h"
#include "../gui/vga.c"
#include "../gui/wm.c"

void kernel_main() {
    vga_init();
    idt_init();
    pic_remap(0x20, 0x28);
    pit_init(100);  // 100 Hz

    vga_clear(0x1A);
    wm_init();

    wm_create_window(50, 30, 220, 140, "FluxOS Terminal");
    wm_create_window(90, 70, 180, 100, "About");

    sti;

    while(1) asm("hlt");
}
