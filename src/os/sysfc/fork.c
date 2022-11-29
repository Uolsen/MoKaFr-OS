#include "sysfc/fork.h"
#include "mm/mm.h"
#include "sched/sched.h"
#include "interrupt/entry.h"
#include "lib.h"

uint32_t copy_process(uint64_t fn, uint64_t arg)
{
	preempt_disable();
	struct task_struct *p;

	p = (struct task_struct *) get_free_page();
	if (!p)
		return 1;
	p->priority = current->priority;
	p->state = TASK_RUNNING;
	p->counter = p->priority;
	p->preempt_count = 1; //disable preemtion until schedule_tail

	p->cpu_context.x19 = fn;
	p->cpu_context.x20 = arg;
	p->cpu_context.pc = (uint64_t)ret_from_fork;
	p->cpu_context.sp = (uint64_t)p + THREAD_SIZE;
	uint32_t pid = nr_tasks++;
	task[pid] = p;	
	preempt_enable();
	return 0;
}