#include "../include/common.h"
#include "../include/elf.h"

typedef struct {
    u32 magic;
    u8  elf_class;
    u8  endianness;
    u8  version;
    u8  osabi;
    u8  abiversion;
    u8  pad[7];
    u16 type;
    u16 machine;
    u32 version2;
    u32 entry;
    u32 phoff;
    u32 shoff;
    u32 flags;
    u16 ehsize;
    u16 phentsize;
    u16 phnum;
    u16 shentsize;
    u16 shnum;
    u16 shstrndx;
} elf_header_t;

typedef struct {
    u32 type;
    u32 offset;
    u32 vaddr;
    u32 paddr;
    u32 filesz;
    u32 memsz;
    u32 flags;
    u32 align;
} elf_program_header_t;

void elf_execute(void* image) {
    elf_header_t* hdr = (elf_header_t*)image;

    if (hdr->magic != 0x464C457F) {
        panic("Not a valid ELF file!");
    }

    // Simple loader: copy segments directly (for ring 3 later)
    for (int i = 0; i < hdr->phnum; i++) {
        elf_program_header_t* ph = (elf_program_header_t*)(image + hdr->phoff + i * hdr->phentsize);
        if (ph->type == 1) {  // PT_LOAD
            memcpy((void*)ph->vaddr, image + ph->offset, ph->filesz);
            if (ph->memsz > ph->filesz) {
                memset((void*)(ph->vaddr + ph->filesz), 0, ph->memsz - ph->filesz);
            }
        }
    }

    // Jump to entry point
    void (*entry)() = (void(*)())hdr->entry;
    entry();
}
