#include "../include/common.h"
#include "../include/idt.h"
#include "../include/isr.h"

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8  zero;
    u8  flags;
    u16 offset_high;
} __attribute__((packed));

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void* isr_table[256];

void idt_set_gate(u8 num, u32 handler) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = 0x08;
    idt[num].zero = 0;
    idt[num].flags = 0x8E;  // Present, ring 0, interrupt gate
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_init(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base = (u32)&idt;

    memset(idt, 0, sizeof(idt));

    for (int i = 0; i < 32; i++) {
        idt_set_gate(i, (u32)isr_table[i]);
    }

    idt_set_gate(32, (u32)isr_table[32]);  // PIT
    idt_set_gate(33, (u32)isr_table[33]);  // Keyboard
    idt_set_gate(44, (u32)isr_table[44]);  // Mouse

    asm volatile("lidt %0" : : "m"(idtp));
}
