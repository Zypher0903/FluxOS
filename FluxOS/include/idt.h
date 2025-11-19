#ifndef IDT_H
#define IDT_H

void idt_init(void);
void idt_set_gate(u8 num, u32 handler);

#endif
