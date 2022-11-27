#include "filesystem/filesystem.h"
#include "stdlib/stdstring.h"

void init_fs() {
    root->parent = (void *) 0x0;
    root->next = (void *) 0x0;
    root->children = root_dev;
    root->is_directory = 1;
    root->driver_id = NO_FILESYSTEM_DRIVER;
    root->name[0] = '\0';

    root_dev->parent = root;
    root_dev->next = root_sys;
    root_dev->children = (void *) 0x0;
    root_dev->is_directory = 1;
    root_dev->driver_id = NO_FILESYSTEM_DRIVER;
    strncpy(root_dev->name, "DEV", 4);

    root_sys->parent = root;
    root_sys->next = root_mnt;
    root_sys->children = (void *) 0x0;
    root_sys->is_directory = 1;
    root_sys->driver_id = NO_FILESYSTEM_DRIVER;
    strncpy(root_sys->name, "SYS", 4);

    root_mnt->parent = root;
    root_mnt->next = (void *) 0x0;
    root_mnt->children = (void *) 0x0;
    root_mnt->is_directory = 1;
    root_mnt->driver_id = NO_FILESYSTEM_DRIVER;
    strncpy(root_mnt->name, "MNT", 4);

    char tmp_name[MAX_FILENAME_LENGTH];
    const char * mp_ptr;
    int i, j;

    for (i = 0; i < FS_drivers_count; i++)
    {
        struct TFS_driver * driver_ptr = FS_drivers[i];
        mp_ptr = driver_ptr->mountPoint;
        struct TFS_tree_node * node = root;
        struct TFS_tree_node * tmp_node = (void *) 0x0;

        while (mp_ptr[0] != '\0') {
            for (j = 0; j < MAX_PATH_LENGTH && mp_ptr[j] != '\0'; j++) {
                if (mp_ptr[j] == ':' || mp_ptr[j] == '/')
                    break;
                tmp_name[j] = mp_ptr[j];
            }

            tmp_name[j] = '\0';
            mp_ptr += j + 1;

            tmp_node = find_child(node, tmp_name);
            // uzel jsme nasli
            if (tmp_node)
                node = tmp_node;
                // uzel jsme nenasli
            else {
                //tmp_node = sKernelMem.Alloc<TFS_Tree_Node>();
                strncpy(tmp_node->name, tmp_name, MAX_FILENAME_LENGTH);
                tmp_node->parent = node;
                tmp_node->children = (void *) 0x0;
                tmp_node->driver_id = NO_FILESYSTEM_DRIVER;
                tmp_node->is_directory = 1;
                tmp_node->next = node->children;
                node->children = tmp_node;

                node = tmp_node;
            }
        }
        // mountpoint nesmi byt uz zabrany
        if (node->driver_id != NO_FILESYSTEM_DRIVER)
            return;
        node->driver_id = i;
        on_register(driver_ptr->driver);
    }


}

struct TFS_tree_node * find_child(struct TFS_tree_node * children, const char* name) {
    struct TFS_tree_node * child = children;
    while (child != (void *) 0x0)
    {
        if (strncmp(child->name, name, MAX_FILENAME_LENGTH) == 0)
            return child;

        child = child->next;
    }

    return (void *) 0x0;
}

struct File * open_file(const char* path, Open_mode mode) {
    char tmp_name[MAX_FILENAME_LENGTH];
    const char * mp_ptr;
    int j;
    mp_ptr = path;
    struct TFS_tree_node * node = root, * tmp_node = (void *) 0x0;

    while (mp_ptr[0] != '\0') {
        for (j = 0; j < MAX_PATH_LENGTH && mp_ptr[j] != '\0'; j++) {
            if (mp_ptr[j] == ':' || mp_ptr[j] == '/')
                break;
            tmp_name[j] = mp_ptr[j];
        }

        tmp_name[j] = '\0';
        mp_ptr += j + 1;

        tmp_node = find_child(node, tmp_name);
        if (tmp_node)
            node = tmp_node;

        if (tmp_node->driver_id != NO_FILESYSTEM_DRIVER)
            return open_driver(FS_drivers[tmp_node->driver_id]->driver, mp_ptr, mode);
        else if (!tmp_node->is_directory)
            break;
    }

    // soubor neexistuje
    return (void *) 0x0;
}