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
    char *strings = strsplit(input, ' ', 0);

    char path[1024] = {0};
    //char * path;
    strncpy(path, "", 1024);
    char * split = get_split(strings, 1);
    strncpy(path, split, strlen(split)-1);
    char *path_tokens = strsplit(path, '/', 0);

    for (uint32_t i = 0; i < 32; i++) {
        char token[32] = {0};
        char *split_t = get_split(path_tokens, i);

        strncpy(token, split_t, strlen(split_t));
        // ../ ../ home/ admin

        if (strlen(token) == 0) {
            continue;
        }
        DEBUG_P("%s", token);

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

void cat(uint8_t *input) {
    char *strings = strsplit(input, ' ', 0);

    char name[32] = {0};
    char *split = get_split(strings, 1);
    strncpy(name, split, strlen(split));

    DEBUG_P("Name: %s", name);
//    DEBUG_P("Split: %s", split);

    Node node = fs_get_node(get_current_node_id());
    Directory *directory = fs_node_get_directory(node);

    DirectoryEntry * entry = fs_get_directory_entry(directory, name);

    Node fileNode = fs_get_node(entry->node_id);
    File * file = fs_node_get_file(fileNode);
    DEBUG_P("File Node: %u", fileNode.id);
//    DEBUG_P("File W Pointer: %u", file->write_pointer);
//    DEBUG_P("File R Pointer: %u", file->read_pointer);

    DEBUG_P("Current Node ID: %u", node.id);
    DEBUG_P("File Node ID: %u", fileNode.id);

//    for (int i = 0; i < 1024; i++) {
//        printp("%s", file->data[i]);
//    }

    char * text = fs_fread(entry, 1024);

    DEBUG_P("Data: %s", text);

}

void draw(input) {
    char *strings = strsplit(input, ' ', 0);
    char data[1024] = {0};
    char *split = get_split(strings, 1);
    strncpy(data, split, strlen(split));
    stradd(data, ";", 1);

    fs_pwrite(get_gfx_pipe(), data, strlen(data));
}