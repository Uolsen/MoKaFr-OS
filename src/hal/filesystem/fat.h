#ifndef MOKAFR_FAT_H
#define MOKAFR_FAT_H

#include "libc.h"

#define FILESYSTEM_SIZE 256
#define MAX_DIRECTORY_ENTRIES 90

typedef struct Node {
    uint8_t used;
    uint32_t next;
    uint64_t page;
} Node;


typedef struct DirectoryEntry {
    uint8_t used;
    uint8_t is_directory;
    uint8_t* name;
    uint32_t node;
    uint32_t size;
} DirectoryEntry;

typedef struct Directory {
    DirectoryEntry entries[MAX_DIRECTORY_ENTRIES];
} Directory;

typedef struct File {

};

uint32_t get_free_node_id();
uint32_t fs_create_node();
void fs_add_directory_entry(Directory* directory, uint8_t is_directory, uint8_t* name);
Node fs_get_node(uint32_t id);

void fs_init();

void fopen();

#endif //MOKAFR_FAT_H
