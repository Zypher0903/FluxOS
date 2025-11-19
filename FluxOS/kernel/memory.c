#include "../include/common.h"

#define HEAP_START  0x100000
#define HEAP_SIZE   0x800000  // 8MB

typedef struct block {
    u32 size;
    u8  used;
    struct block* next;
} block_t;

block_t* heap_head = (block_t*)HEAP_START;

void memory_init(void) {
    heap_head->size = HEAP_SIZE - sizeof(block_t);
    heap_head->used = 0;
    heap_head->next = NULL;
}

void* malloc(u32 size) {
    block_t* b = heap_head;
    while (b) {
        if (!b->used && b->size >= size) {
            if (b->size > size + sizeof(block_t)) {
                block_t* split = (block_t*)((u32)b + sizeof(block_t) + size);
                split->size = b->size - size - sizeof(block_t);
                split->used = 0;
                split->next = b->next;
                b->next = split;
            }
            b->used = 1;
            b->size = size;
            return (void*)((u32)b + sizeof(block_t));
        }
        b = b->next;
    }
    return NULL;
}

void free(void* ptr) {
    if (!ptr) return;
    block_t* b = (block_t*)((u32)ptr - sizeof(block_t));
    b->used = 0;
}
