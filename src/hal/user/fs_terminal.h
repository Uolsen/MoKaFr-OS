#ifndef MOKAFR_MKDIR_H
#define MOKAFR_MKDIR_H

#include "intdef.h"

void mkdir(uint8_t * input);
void touch (uint8_t *input);
void ls();
uint32_t cd(uint32_t current_node_id, uint8_t * input);
void pwd();
void cat(uint8_t *input);
void draw(input);

#endif //MOKAFR_MKDIR_H
