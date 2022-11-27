#ifndef _FORK_H
#define _FORK_H

#include "lib.h"

uint32_t copy_process(uint64_t fn, uint64_t arg);
void ret_from_fork(void);

#endif