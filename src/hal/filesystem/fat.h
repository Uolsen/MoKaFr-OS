#ifndef MOKAFR_FAT_H
#define MOKAFR_FAT_H

#include "libc.h"

#define FILESYSTEM_SIZE 256
#define MAX_DIRECTORY_ENTRIES 90
#define MAX_PATH_SIZE 1024

typedef struct Node {
    uint8_t used;
    uint32_t id;
    uint64_t page;
    uint8_t w;
    uint8_t r;
} Node;


typedef struct DirectoryEntry {
    uint8_t used;
    uint8_t is_directory;
    uint8_t name[32];
    uint32_t node_id;
    uint32_t size;
} DirectoryEntry;

typedef struct Directory {
    DirectoryEntry entries[MAX_DIRECTORY_ENTRIES];
} Directory;

typedef struct File {

} File;

typedef struct Pipe {

} Pipe;

uint32_t get_free_node_id();
//uint32_t fs_create_node();
uint8_t fs_check_name(Directory *directory, uint8_t *name);
void fs_create_directory(Node parent, uint8_t* name);
void fs_create_file(Node parent, uint8_t* name);
Node fs_get_node(uint32_t id);
char * fs_get_name_by_node_id(Directory * directory, uint32_t id);
Directory * fs_node_get_directory(Node node);
File * fs_node_get_file(Node node);
char * fs_get_path(Node node);
void fs_init();
DirectoryEntry *fs_add_directory_entry(Directory *directory, uint8_t is_directory, uint8_t *name);
DirectoryEntry * fs_get_directory_entry(Directory * directory, uint8_t * name);
DirectoryEntry * fs_get_parent_directory_entry(Directory * directory);
DirectoryEntry * fs_get_current_directory_entry(Directory * directory);


#endif //MOKAFR_FAT_H
