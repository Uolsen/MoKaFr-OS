#include "filesystem/fat.h"
#include "debug/debug.h"
#include "stdlib/stdstring.h"

static Node file_system[FILESYSTEM_SIZE];
static char path[MAX_PATH_SIZE];
static DirectoryEntry * GFX_PIPE;

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
//    node.next = 0;
    node.page = get_free_page();
    node.id = node_id;
    node.w = 0;
    node.r = 0;

    file_system[node_id] = node;

    bzero(node.page, 5460);

    return node_id;
}

Directory *fs_node_get_directory(Node node) {
    return (Directory *) node.page;
}

File *fs_node_get_file(Node node) {
    return (File *) node.page;
}

Pipe *fs_node_get_pipe(Node node) {
    return (Pipe *) node.page;
}

char * fs_get_name_by_node_id(Directory * directory, uint32_t id) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (directory->entries[i].node_id == id) {
//            DEBUG_P("get_name %s", directory->entries[i].name);
            return directory->entries[i].name;
        }
    }
}

char *fs_get_path(Node node) {

//    DEBUG_P("start node id %u", node.id);
    // Get current node
    if (node.id == 1) {
        return "/";
    }

    bzero(path, MAX_PATH_SIZE);

    while (node.id != 1) {
        Directory *directory = fs_node_get_directory(node);
        DirectoryEntry * parentEntry = fs_get_parent_directory_entry(directory);
        Node parentNode = fs_get_node(parentEntry->node_id);
        Directory * parentDirectory = fs_node_get_directory(parentNode);
        char * name = fs_get_name_by_node_id(parentDirectory, node.id);

//        DEBUG_P("parent node id %u", parentNode.id);
//        DEBUG_P("node id %u", node.id);
//        DEBUG_P("name %s", name);
        straddtostart(name, path);
        straddtostart("/", path);
        node = fs_get_node(parentEntry->node_id);

    }

    return path;

    // Cast node.page -> directory -> get entries -> get .. (ID 1)
    // Repeat
}

uint8_t fs_check_name(Directory *directory, uint8_t *name) {
    for (uint32_t j = 0; j < strlen(name); j++) {
//        DEBUG_P("a %u", (uint8_t)'a'); //97
//        DEBUG_P("z %u", (uint8_t)'z'); // 122
//        DEBUG_P("A %u", (uint8_t)'A'); // 65
//        DEBUG_P("Z %u", (uint8_t)'Z'); // 90
//        DEBUG_P("0 %u", (uint8_t)'0'); // 48
//        DEBUG_P("9 %u", (uint8_t)'9'); // 59
        if (!(
                (name[j] >= 'a' && name[j] <= 'z') ||
                (name[j] >= 'A' && name[j] && name[j] <= 'Z') ||
                (name[j] >= '0' && name[j] && name[j] <= '9')
                )) {
            return 0;
        }
    }

    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (strncmp(directory->entries[i].name, name, strlen(name)) == 0) {
            return 0;
        }
    }

    return 1;
}

DirectoryEntry *fs_add_directory_entry_with_link(Directory *directory, uint8_t *name, uint32_t target_id) {
    DirectoryEntry *entry;

    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (!directory->entries[i].used) {
            entry = &directory->entries[i];
            break;
        }
    }

    entry->is_directory = 1;
    entry->node_id = target_id;
    strncpy(entry->name, name, strlen(name));
//    entry->name = name;
    entry->used = 1;

    return entry;
}

DirectoryEntry *fs_add_directory_entry(Directory *directory, uint8_t is_directory, uint8_t *name) {
    if (!fs_check_name(directory, name)) {
        print("Use other name!");
        return;
    }

    DirectoryEntry *entry;
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (!directory->entries[i].used) {
            entry = &directory->entries[i];
            break;
        }
    }


    entry->is_directory = is_directory;
    entry->node_id = fs_create_node();
    strncpy(entry->name, name, strlen(name));
//    entry->name = name;
    entry->used = 1;

    return entry;
}

DirectoryEntry * fs_create_file(Node parent, uint8_t *name) {
    // Cast node to Directory
    Directory *parentDirectory = (Directory *) parent.page;

    return fs_add_directory_entry(parentDirectory, 0, name);
    // create file node
    // create directory entry for parent
    // associate node with entry
}

DirectoryEntry * fs_create_pipe(Node parent, uint8_t *name) {
    // Cast node to Directory
    Directory *parentDirectory = (Directory *) parent.page;

    DirectoryEntry * entry =  fs_add_directory_entry(parentDirectory, 0, name);

    Node node = fs_get_node(entry->node_id);
    Pipe * pipe = fs_node_get_pipe(node);
    pipe->read_pointer = 0;
    pipe->write_pointer = 0;

    return entry;
    // create file node
    // create directory entry for parent
    // associate node with entry
}

DirectoryEntry * fs_create_directory(Node parent, uint8_t *name) {
    // Cast node to Directory
    Directory *parentDirectory = (Directory *) parent.page;

    // create directory node
    DirectoryEntry *entry = fs_add_directory_entry(parentDirectory, 1, name);
    Directory *directory = (Directory *) fs_get_node(entry->node_id).page;

    // create directory entry for parent
    fs_add_directory_entry_with_link(directory, ".", entry->node_id);
    fs_add_directory_entry_with_link(directory, "..", parent.id);

    // create entries for current / parent
    // associate node with entry
    return entry;
}

DirectoryEntry *fs_get_directory_entry(Directory *directory, uint8_t *name) {
    for (uint32_t i = 0; i < MAX_DIRECTORY_ENTRIES; i++) {
        if (strncmp(directory->entries[i].name, name, strlen(name)) == 0) {
            return &directory->entries[i];
        }
    }
}

DirectoryEntry *fs_get_parent_directory_entry(Directory *directory) {
    return fs_get_directory_entry(directory, "..");
}

DirectoryEntry *fs_get_current_directory_entry(Directory *directory) {
    return fs_get_directory_entry(directory, ".");
}

void fs_clear() {
    for (uint32_t i = 0; i < FILESYSTEM_SIZE; i++) {
        file_system[i].used = 0;
    }
}

void fs_fwrite(DirectoryEntry * entry, uint8_t * data, uint32_t size) {
    if (entry->is_directory == 1) {
        print("Cannot write to directory");
        return;
    }

    Node node = fs_get_node(entry->node_id);

    if (node.w) {
        print("Node is being written to already");
        return;
    }

    File * file = (File *) node.page;

    if ((strlen(file->data) + size) > PAGE_SIZE) {
        print("Not enough space");
        return;
    }

    stradd(file->data, data, size);
}

uint8_t * fs_fread(DirectoryEntry * entry, uint32_t size) {
    if (entry->is_directory == 1) {
        print("Cannot read from directory");
        return;
    }

    Node node = fs_get_node(entry->node_id);

    if (node.r) {
        print("Node is being read from already");
        return;
    }

    File * file = (File *) node.page;

    DEBUG_P("FREAD ADDR: %x", file->data);
    DEBUG_P("FREAD READ: %s", file->data);

    return file->data;
}

void fs_pwrite(DirectoryEntry * entry, uint8_t * data, uint32_t size) {
    if (entry->is_directory == 1) {
        print("Cannot write to directory");
        return;
    }
//    DEBUG_P("DATA: %s", data);

    Node node = fs_get_node(entry->node_id);

    if (node.w) {
        print("Node is being written to already");
        return;
    }
    node.w = 1;
    Pipe * pipe = (Pipe *) node.page;

    for (int i = 0; i < strlen(data); i++) {
        uint32_t index = (pipe->write_pointer + i) % (PAGE_SIZE - (2 * 4));
        pipe->data[index] = data[i];
    }

    pipe->write_pointer = (pipe->write_pointer + size) % (PAGE_SIZE - (2 * 4));
//    DEBUG_P("data write %s", pipe->data);
    node.w = 0;
}

uint8_t fs_pread(DirectoryEntry * entry) {
    if (entry->is_directory == 1) {
        print("Cannot read from directory");
        return;
    }

    Node node = fs_get_node(entry->node_id);

    if (node.r) {
        print("Node is being read from already");
        return;
    }

    Pipe * pipe = (Pipe *) node.page;

//    uint8_t buffer[size];
//    for (int i = 0; i < size; i++) {
//        int index = (pipe->read_pointer + i) % (PAGE_SIZE - (2 * 4));
////        DEBUG_P("READ PINTER: %u", pipe->read_pointer);
//        buffer[i] = pipe->data[index];
//    }
    int index = (pipe->read_pointer) % (PAGE_SIZE - (2 * 4));
    uint8_t character = pipe->data[index];
    pipe->read_pointer = (pipe->read_pointer + 1) % (PAGE_SIZE - (2 * 4));
//pipe->read_pointer = 0;

    DEBUG_P("PREAD READ: %s", pipe->data);

    return character;
}

DirectoryEntry * fs_find_directory_entry(Directory * directory, char * path) {
//
//    char * tokens = strsplit(path, '/', 0);
//
//    for (uint32_t i = 0; i < 32; i++) {
//        char token[32] = {0};
//        char *split_t = get_split(tokens, i);
//
//        strncpy(token, split_t, strlen(split_t));
//        // ../ ../ home/ admin
//
//        if (strlen(token) == 0) {
//            continue;
//        }
//        DEBUG_P("%s", token);
//
//        Node node = fs_get_node(current_node_id);
//        Directory *directory = fs_node_get_directory(node);
//
//        for (uint32_t j = 0; j < MAX_DIRECTORY_ENTRIES; j++) {
//            if (strncmp(directory->entries[j].name, token, strlen(token)) == 0) {
//                if (directory->entries[j].is_directory == 0) {
//                    print("Cannot move to file!");
//                    return original_node_id;
//                }
//                //   DEBUG_F("Changed current node");
//                current_node_id = directory->entries[j].node_id;
//                break;
//            }
//        }
//    }

    Node root = fs_get_node(1);
    Directory * root_directory = fs_node_get_directory(root);
    DirectoryEntry * dev_entry = fs_get_directory_entry(root_directory, "dev");

    Node dev_node = fs_get_node(dev_entry->node_id);
    Directory * dev_directory = fs_node_get_directory(dev_node);

    return fs_get_directory_entry(dev_directory, "gfx");

}

DirectoryEntry * get_gfx_pipe() {
    return GFX_PIPE;
}


void fs_init() {
    DEBUG_F("Initializing FS...");
    fs_clear();

    uint32_t id = fs_create_node();

    Node root = file_system[id];
    Directory *rootDirectory = (Directory *) root.page;
    fs_add_directory_entry_with_link(rootDirectory, ".", root.id);
    fs_add_directory_entry_with_link(rootDirectory, "..", root.id);
    fs_create_directory(root, "sys");
    DirectoryEntry * devEntry = fs_create_directory(root, "dev");
    fs_create_directory(root, "mnt");

    // Create pipes
    GFX_PIPE = fs_create_file(fs_get_node(devEntry->node_id), "gfx");

    DEBUG_P("GFX PIPE addr: %x", GFX_PIPE);

    uint8_t * text = "string|100|100|Hallooooo!|0x13;circle|50|50|50|0x13|1;rect|200|200|300|300|0x2e|1;";
  //  fs_pwrite(GFX_PIPE, text, strlen(text));
//    fs_pread(GFX_PIPE);
   // fs_fread(GFX_PIPE, strlen(text));
}