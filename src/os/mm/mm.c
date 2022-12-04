#include "mm/mm.h"

static unsigned short mem_map[PAGING_PAGES] = {0,};

/**
 * Returns a free page.
 *
 * @return
 */
unsigned long get_free_page() {
    for (int i = 0; i < PAGING_PAGES; i++) {
        if (mem_map[i] == 0) {
            mem_map[i] = 1;
            return LOW_MEMORY + i * PAGE_SIZE;
        }
    }
    return 0;
}

/**
 * Frees the page at the given index.
 *
 * @param p Index of the page
 */
void free_page(unsigned long p) {
    mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}