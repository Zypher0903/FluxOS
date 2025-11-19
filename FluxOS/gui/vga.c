// gui/vga.c
#include "../include/common.h"
#include "../include/vga.h"

static u8 *vga = (u8*)VGA_BUFFER;

u8 font8x8[128][8] = {
    // samo deo (space, A-Z, 0-9, [X], etc.)
    // pun font možeš prekopirati sa osdev.org ili linux/drivers/video/console/font_8x8.c
    [32] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['A'] = {0x18,0x24,0x42,0x42,0x7E,0x42,0x42,0x00},
    ['X'] = {0x42,0x24,0x18,0x18,0x18,0x24,0x42,0x00},
    // ... dodaj ostale ako hoćeš lepši tekst
};

void vga_putpixel(int x, int y, u8 color) {
    if (x >= 0 && x < 320 && y >= 0 && y < 200)
        vga[y * 320 + x] = color;
}

void vga_clear(u8 color) {
    for (int i = 0; i < 64000; i++) vga[i] = color;
}

void vga_fillrect(int x, int y, int w, int h, u8 color) {
    for (int j = y; j < y+h; j++)
        for (int i = x; i < x+w; i++)
            vga_putpixel(i, j, color);
}

void vga_drawchar(char c, int x, int y, u8 fg, u8 bg) {
    if (c < 0 || c > 127) c = '?';
    for (int i = 0; i < 8; i++) {
        u8 line = font8x8[(u8)c][i];
        for (int j = 0; j < 8; j++) {
            vga_putpixel(x+j, y+i, (line & (1<<(7-j))) ? fg : bg);
        }
    }
}

void vga_drawstring(const char *s, int x, int y, u8 color) {
    while (*s) {
        vga_drawchar(*s++, x, y, color, 0);
        x += 8;
    }
}
