#include "filesystem/fat.h"
#include "debug/debug.h"
#include "stdlib/stdstring.h"

static Node file_system[FILESYSTEM_SIZE];

Node fs_get_node(uint32_t id) {
    return file_system[id];
}

uint32_t get_free_node_id() {
    for (uint32_t i = 1; i < FILESYSTEM_SIZE; i++) {
        DEBUG_P("Free Node ID: %u", i);
        if (!file_system[i].used) {
            return i;
        }
    }
    DEBUG_F("Filesystem is full!");
    return 0;
}

uint32_t fs_create_node() {
    uint32_t node_id = get_free_node_id();

    if (node_id == 0) {
//        return 0;
        // error
    }

    Node node;
    node.used = 1;
    node.next = 0;
    node.page = get_free_page();
    node.id = node_id;

    file_system[node_id] = node;

    return node_id;
}

Directory * fs_node_get_directory(Node node) {
    return (Directory *) node.page;
}

File * fs_node_get_file(Node node) {
    return (File *) node.page;
}

DirectoryEntry * fs_add_directory_entry_with_link(Directory * directory, uint8_t * name, uint32_t target_id) {
    DirectoryEntry * entry;
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (!directory->entries[i].used) {
//            DEBUG_F("Writing an entry");
//            directory->entries[i] = entry;
            entry = &directory->entries[i];
            break;
        }
    }

    entry->is_directory = 1;
    entry->node_id = target_id;
    entry->name = name;
    entry->used = 1;


    return entry;
}

DirectoryEntry * fs_add_directory_entry(Directory* directory, uint8_t is_directory, uint8_t* name) {
    DirectoryEntry * entry;
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (!directory->entries[i].used) {
            entry = &directory->entries[i];
            break;
        }
    }


    entry->is_directory = is_directory;
    entry->node_id = fs_create_node();
    entry->name = name;
    entry->used = 1;

    return entry;
}

void fs_create_file(Node parent, uint8_t* name) {
    // Cast node to Directory
    Directory* parentDirectory = (Directory*) parent.page;

    fs_add_directory_entry(parentDirectory, 0, name);
    // create file node
    // create directory entry for parent
    // associate node with entry
}

void fs_create_directory(Node parent, uint8_t* name) {
    // Cast node to Directory
    Directory* parentDirectory = (Directory*) parent.page;

    // create directory node
    DirectoryEntry * entry = fs_add_directory_entry(parentDirectory, 1, name);
    Directory * directory = (Directory *) fs_get_node(entry->node_id).page;

    // create directory entry for parent
    fs_add_directory_entry_with_link(directory, ".", entry->node_id);
    fs_add_directory_entry_with_link(directory, "..", parent.id);

    // create entries for current / parent
    // associate node with entry
}

void fs_clear() {
    for (uint32_t i = 0; i < FILESYSTEM_SIZE; i++) {
        file_system[i].used = 0;
    }
}

void fs_init() {
    DEBUG_F("Initializing FS...");
    fs_clear();

    uint32_t id = fs_create_node();

    Node root = file_system[id];
    Directory* rootDirectory = (Directory*) root.page;
    fs_add_directory_entry_with_link(rootDirectory, ".", rootDirectory);
    fs_add_directory_entry_with_link(rootDirectory, "..", rootDirectory);
    fs_add_directory_entry(rootDirectory, 1, "sys");
    fs_add_directory_entry(rootDirectory, 1, "dev");
    fs_add_directory_entry(rootDirectory, 1, "mnt");

}

void fopen() {

}
