#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include "intdef.h"
#include "stdlib/stdfile.h"

#define MAX_FS_DRIVERS_NAME_LENGTH 16
#define MAX_FILENAME_LENGTH 16
#define MAX_PATH_LENGTH 128
#define NO_FILESYSTEM_DRIVER (uint32_t) -1

typedef enum {
    GPIO_FS,
    UART_FS,
} FS_type;

struct File {
    struct File * file;
};

struct FS_driver {
    struct FS_driver * driver;
};

struct TFS_tree_node {
    char name[MAX_FILENAME_LENGTH];
    uint8_t is_directory;
    uint32_t driver_id;
    struct TFS_tree_node * parent;
    struct TFS_tree_node * children;
    struct TFS_tree_node * next;
};

struct TFS_driver {
    char name[MAX_FS_DRIVERS_NAME_LENGTH];
    const char * mountPoint;
    struct FS_driver * driver;
};

// tabulka driveru
static struct TFS_driver * FS_drivers[];
static uint32_t FS_drivers_count;

struct TFS_tree_node * root;
struct TFS_tree_node * root_dev;
struct TFS_tree_node * root_sys;
struct TFS_tree_node * root_mnt;

void init_fs();
struct File * open_file(const char* path, Open_mode mode);
struct TFS_tree_node * find_child(struct TFS_tree_node * children, const char* name);


void on_register(struct FS_driver * driver);
struct File * open_driver(struct FS_driver * driver, const char* path, Open_mode mode);

#endif
