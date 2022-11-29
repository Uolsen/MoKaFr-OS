#include "filesystem/fat.h"
#include "debug/debug.h"
#include "stdlib/stdstring.h"

static Node file_system[FILESYSTEM_SIZE];

Node fs_get_node(uint32_t id) {
    return file_system[id];
}

uint32_t get_free_node_id() {
    for (uint32_t i = 1; i < FILESYSTEM_SIZE; i++) {
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

    file_system[node_id] = node;

    return node_id;
}

void fs_add_directory_entry(Directory* directory, uint8_t is_directory, uint8_t* name) {
    DirectoryEntry entry;
    entry.is_directory = is_directory;
//    strncpy(*entry.name, name, strlen(name));
//    entry.name = name;

    DEBUG_P("name: %s", name);
    uint32_t i;
//    for (i = 0; i < 32; i++) {
//        if (name[i] != '\0') {
//            entry.name[i] = name[i];
//        } else {
//            entry.name[i] = '\0';
//        }
//    }


    entry.node = fs_create_node();
    entry.name = name;
    entry.used = 1;


    for (i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (!directory->entries[i].used) {
            DEBUG_F("Writing an entry");
            directory->entries[i] = entry;
            break;
        }
    }

}


void fs_init() {
    DEBUG_F("Initializing FS...");

    uint32_t id = fs_create_node();

    Node * root = &file_system[id];
    Directory* rootDirectory = (Directory*) root->page;
    fs_add_directory_entry(rootDirectory, 1, "sys");
    fs_add_directory_entry(rootDirectory, 1, "dev");
    fs_add_directory_entry(rootDirectory, 1, "mnt");


//    Node root;
//    root.used = 1;
//    root.next = 0;
//    root.page = get_free_page();
//    file_system[1] = root;
//
//    Node sysNode;
//    sysNode.used = 1;
//    sysNode.next = 0;
//    sysNode.page = get_free_page();
//
//    DirectoryEntry sys;
//    sys.is_directory = 1;
//    sys.name = "sys";
//    sys.node_id =
//
//            DirectoryEntry
//    testFileEntry;
//    testFileEntry.is_directory = 0;
//    testFileEntry.name = "test";
//    testFileEntry.node_id = 2;
//
//    Node testFileNode;
//    testFileNode.used = 1;
//    testFileNode.next = 0;
//    testFileNode.page = get_free_page();
//
//    file_system[2] = testFileNode;
//
//    Directory rootDirectory = (struct Directory *) *root.page;
//    rootDirectory.entries[0] = testFileEntry;
//    rootDirectory.entries[1] = sys;
//
//    root.entries[0].name


//    DirectoryEntry dev;
//    sys.name = "dev";
//
//    DirectoryEntry mnt;
//    sys.name = "mnt";


    // Calculate Filesystem size

//    Directory root;
//    root.entries[0] = dev;
//    root.entries[1] = mnt;
//    root.entries[2] = sys;
    // Define ROOT directory
    // Define SYS directory
    // Define MNT directory
    // Define DEV directory

}

void fopen() {

}
