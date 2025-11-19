#ifndef VGA_H
#define VGA_H

#define VGA_WIDTH  320
#define VGA_HEIGHT 200
#define VGA_BUFFER 0xA0000

void vga_putpixel(int x, int y, u8 color);
void vga_clear(u8 color);
void vga_drawrect(int x, int y, int w, int h, u8 color);
void vga_fillrect(int x, int y, int w, int h, u8 color);
void vga_drawchar(char c, int x, int y, u8 fg, u8 bg);
void vga_drawstring(const char *str, int x, int y, u8 color);

extern u8 font8x8[128][8];

#endif
