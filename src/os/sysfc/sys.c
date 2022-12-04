#include "sysfc/fork.h"
#include "print/print.h"
#include "lib.h"
#include "sched/sched.h"
#include "mm/mm.h"

void sys_write(char * buf){
	print(buf);
}

int sys_clone(unsigned long stack){
	return copy_process(0, 0, 0, stack);
}

/**
 * Allocates a free page.
 * @return
 */
unsigned long sys_malloc(){
	unsigned long addr = get_free_page();
	if (!addr) {
		return -1;
	}
	return addr;
}

/**
 * Exits the system process.
 */
void sys_exit(){
	exit_process();
}

/**
 * Returns the current EL level.
 *
 * @return
 */
long sys_get_el(){
	return get_el();
}

void * const sys_call_table[] = {sys_write, sys_malloc, sys_clone, sys_exit, sys_get_el};
