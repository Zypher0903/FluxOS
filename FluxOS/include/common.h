#ifndef COMMON_H
#define COMMON_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

#define NULL 0
void outb(u16 port, u8 val);
u8 inb(u16 port);
void* memset(void* s, int c, u32 n);
void* memcpy(void* d, const void* s, u32 n);
int strlen(const char* s);

extern void panic(const char* msg);

#endif
