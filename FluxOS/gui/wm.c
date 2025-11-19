// gui/wm.c
#include "../include/common.h"
#include "../include/wm.h"
#include "../gui/vga.c"

#define MAX_WINDOWS 8
typedef struct { int x,y,w,h; char title[32]; int active; } window_t;
window_t windows[MAX_WINDOWS];
int window_count = 0;
int active_window = -1;
int dragging = 0;

void wm_init() {
    vga_clear(0x1A);
    vga_fillrect(0, 180, 320, 20, 0x08);
    vga_print("FluxOS v5.0", 5, 185, 0x0F);
}

void wm_create_window(int x, int y, int w, int h, const char* title) {
    if (window_count >= MAX_WINDOWS) return;
    window_t* win = &windows[window_count++];
    win->x = x; win->y = y; win->w = w; win->h = h;
    strcpy(win->title, title);
    win->active = 1;

    vga_fillrect(x, y, w, h, 0x0F);
    vga_fillrect(x, y, w, 20, 0x1F);
    vga_print(title, x+5, y+5, 0x00);
    vga_print("[X]", x+w-25, y+5, 0x0C);
}

void wm_draw_mouse(int x, int y) {
    static int oldx = -1, oldy = -1;
    if (oldx != -1) vga_putpixel(oldx, oldy, 0x1A);
    vga_putpixel(x, y, 15);
    vga_putpixel(x+1, y+1, 15);
    oldx = x; oldy = y;
}
