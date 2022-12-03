#ifndef MOKAFR_MKDIR_H
#define MOKAFR_MKDIR_H

#include "intdef.h"

void mkdir(char * input);
void touch (char *input);
void ls();
uint32_t cd(uint32_t current_node_id, char * input);
void pwd();

#endif //MOKAFR_MKDIR_H
