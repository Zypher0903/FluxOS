#include "../include/common.h"

struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8  base_mid;
    u8  access;
    u8  granularity;
    u8  base_high;
} __attribute__((packed));

struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

struct gdt_entry gdt[5];
struct gdt_ptr gp;

void gdt_set_gate(int num, u32 base, u32 limit, u8 access, u8 gran) {
    gdt[num].base_low = base & 0xFFFF;
    gdt[num].base_mid = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = limit & 0xFFFF;
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_init(void) {
    gp.limit = sizeof(gdt) - 1;
    gp.base = (u32)&gdt;

    gdt_set_gate(0, 0, 0, 0, 0);                    // Null
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);     // Code
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);     // Data
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);     // User code
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);     // User data

    asm volatile("lgdt %0" : : "m"(gp));
    asm volatile(
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "pushl $0x08\n"
        "pushl $1f\n"
        "retf\n"
        "1:\n"
        : : "a"(0x10)
    );
}
