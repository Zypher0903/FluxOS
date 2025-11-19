// kernel/idt.c
#include "../include/common.h"
#include "../include/isr.h"

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8 zero;
    u8 type_attr;
    u16 offset_high;
} __attribute__((packed));

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void* isr_stub_table[];

void idt_set_gate(u8 num, u32 offset, u16 selector, u8 type_attr) {
    idt[num].offset_low = offset;
    idt[num].offset_low = offset & 0xFFFF;
    idt[num].offset_high = (offset >> 16) & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
}

void idt_init() {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (u32)&idt;

    for(int i = 0; i < 32; i++)
        idt_set_gate(i, (u32)isr_stub_table[i], 0x08, 0x8E);

    idt_set_gate(0x20, (u32)isr32, 0x08, 0x8E);  // PIT
    idt_set_gate(0x21, (u32)isr33, 0x08, 0x8E);  // Keyboard
    idt_set_gate(0x2C, (u32)isr44, 0x08, 0x8E);  // Mouse (IRQ12)

    asm volatile("lidt %0" : : "m"(idtp));
}
