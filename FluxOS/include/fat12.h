#ifndef FAT12_H
#define FAT12_H

#include "common.h"

#define SECTOR_SIZE 512
#define CLUSTER_SIZE 512

typedef struct {
    u8  jmp[3];
    u8  oem[8];
    u16 bytes_per_sector;
    u8  sectors_per_cluster;
    u16 reserved_sectors;
    u8  fat_copies;
    u16 root_entries;
    u16 total_sectors;
    u8  media_descriptor;
    u16 sectors_per_fat;
    u16 sectors_per_track;
    u16 heads;
    u32 hidden_sectors;
    u32 large_sector_count;
} __attribute__((packed)) fat12_bpb_t;

typedef struct {
    char filename[8];
    char ext[3];
    u8  attributes;
    u8  reserved[10];
    u16 time;
    u16 date;
    u16 start_cluster;
    u32 file_size;
} __attribute__((packed)) fat12_direntry_t;

void fat12_init(void);
void* fat12_load_file(const char* filename, u32* size_out);

#endif
