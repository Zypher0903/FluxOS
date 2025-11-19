#include "../include/common.h"
#include "../include/fat12.h"

void kernel_main(void) {
    gdt_init();
    idt_init();
    pic_remap(0x20, 0x28);
    pit_init(100);
    memory_init();
    fat12_init();

    vga_init();
    wm_init();

    // Test ELF loader
    u32 size;
    void* hello = fat12_load_file("HELLO  ELF", &size);
    if (hello) {
        elf_execute(hello);
    }

    asm volatile("sti");
    while (1) asm("hlt");
}
