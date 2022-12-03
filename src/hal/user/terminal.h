#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "intdef.h"

enum state
{
	term_input,
	term_working,
	
};

void terminal_main();
uint32_t get_current_node_id();

#endif