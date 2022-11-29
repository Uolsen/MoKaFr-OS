#ifndef _SCHED_H
#define _SCHED_H

#define THREAD_SIZE				4096

#define NR_TASKS				64 

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#define TASK_RUNNING				0
#define TASK_ZOMBIE					1

#include "lib.h"

extern struct task_struct *current;
extern struct task_struct * task[NR_TASKS];
extern uint32_t nr_tasks;

struct cpu_context {
	uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t fp;
	uint64_t sp;
	uint64_t pc;
};

struct task_struct {
	struct cpu_context cpu_context;
	int64_t state;	
	int64_t counter;
	int64_t priority;
	int64_t preempt_count;
	uint64_t stack;
	uint64_t flags;
};

void sched_init(void);
void schedule(void);
void timer_tick(void);
void preempt_disable(void);
void preempt_enable(void);
void switch_to(struct task_struct* next);
void cpu_switch_to(struct task_struct* prev, struct task_struct* next);
extern void exit_process(void);

#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	0,0,1, 0 \
}

#endif
