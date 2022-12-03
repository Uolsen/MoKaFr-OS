#include "user/fs_terminal.h"
#include "user/terminal.h"
#include "stdlib/stdstring.h"
#include "debug/debug.h"
#include "filesystem/fat.h"

void mkdir(char *input) {
    char **strings = strsplit(input, ' ', 0);

    char *name;
    strncpy(name, strings + (1 * 8 * 16), 16);
    Node node = fs_get_node(get_current_node_id());
//    Directory * directory = fs_node_get_directory(node);
    fs_create_directory(node, name);
//    fs_add_directory_entry(directory, 1, name);
}

void touch (char *input) {
    char **strings = strsplit(input, ' ', 0);

    char *name;
    strncpy(name, strings + (1 * 8 * 16), 16);
    Node node = fs_get_node(get_current_node_id());

    fs_create_file(node, name);
}

void ls() {
    Directory *directory = fs_node_get_directory(fs_get_node(get_current_node_id()));
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (directory->entries[i].used) {
            int64_t params[] = {(uint32_t) directory->entries[i].node_id, (uint32_t) directory->entries[i].is_directory,
                                directory->entries[i].name};
            printk("%u %u %s\r\n", params);
        }
    }
}

uint32_t cd(uint32_t current_node_id, char *input) {
    uint32_t original_node_id = current_node_id;
    char **strings = strsplit(input, ' ', 0);

    char *path;
    strncpy(path, strings + (1 * 8 * 16), 16);
    char **path_tokens = strsplit(path, '/', 0);

    for (uint32_t i = 0; i < 32; i++) {
        char *token;
        strncpy(token, path_tokens + (i * 8 * 16), 16);
        // ../ ../ home/ admin
        DEBUG_P("%s", token);

        if (strlen(token) == 0) {
            continue;
        }

        Node node = fs_get_node(current_node_id);
        Directory *directory = fs_node_get_directory(node);

        for (uint32_t j = 0; j < MAX_DIRECTORY_ENTRIES; j++) {
            if (strncmp(directory->entries[j].name, token, strlen(token)) == 0) {
                if (directory->entries[j].is_directory == 0) {
                    print("Cannot move to file!");
                    return original_node_id;
                }
                DEBUG_F("Changed current node");
                current_node_id = directory->entries[j].node_id;
                break;
            }
        }
    }

    return current_node_id;
}

void pwd() {
    Node node = fs_get_node(get_current_node_id());
    DEBUG_P("NODE ID %u", node.id);
    char *path = fs_get_path(node);
    printp("%s", path);
}