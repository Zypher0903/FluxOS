// include/pic.h
void pic_remap(int offset1, int offset2);
void pic_eoi(u8 irq);

// include/pit.h
void pit_init(u32 frequency);

// include/wm.h
void wm_init(void);
void wm_create_window(int x, int y, int w, int h, const char* title);
void wm_draw_mouse(int x, int y);
void wm_handle_mouse(int x, int y, int btn);
