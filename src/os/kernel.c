#include "uart/uart.h"
#include "print/print.h"
#include "lib.h"
#include "debug/debug.h"
#include "timer/arm_timer.h"
#include "timer/system_timer.h"
#include "sysfc/fork.h"
#include "sysfc/sys.h"
#include "interrupt/gic400.h"
#include "sched/sched.h"
#include "filesystem/fat.h"

#include "user/terminal.h"

void user_process1(char *array)
{
	char buf[2] = {0};
	while (1){
		for (int i = 0; i < 5; i++){
			buf[0] = array[i];
			print(buf);
			delay(100000);
		}
	}
}

void user_process(){
	char buf[30] = {0};
	print("User process started\n\r");
    // printp("Moved to EL %u\r\n", (uint64_t)call_sys_get_el());
	print(buf);
	call_sys_write(buf);

    unsigned long stack = call_sys_malloc();
	if (stack < 0) {
		print("Error while allocating stack for process 1\n\r");
		return;
	}	
    int err = call_sys_clone((unsigned long)&terminal_main, (unsigned long)"", stack);
	if (err < 0){
		print("Error while clonning process 1\n\r");
		return;
	} 

	// unsigned long stack = call_sys_malloc();
	// if (stack < 0) {
	// 	print("Error while allocating stack for process 1\n\r");
	// 	return;
	// }
	// int err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"12345", stack);
	// if (err < 0){
	// 	print("Error while clonning process 1\n\r");
	// 	return;
	// } 
	// stack = call_sys_malloc();
	// if (stack < 0) {
	// 	print("Error while allocating stack for process 1\n\r");
	// 	return;
	// }
	// err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"abcd", stack);
	// if (err < 0){
	// 	print("Error while clonning process 2\n\r");
	// 	return;
	// } 
	call_sys_exit();
}

void kernel_process(){
	printp("Kernel process started. EL %u\r\n", (uint64_t)get_el());
	int err = move_to_user_mode((unsigned long)&user_process);
	if (err < 0){
		print("Error while moving process to user mode\n\r");
	} 
}

void main()
{
    init_uart();
    fb_init();
    fs_init();
//    DEBUG_P("main used %u", fsget_node[1].used);


    Node root = fs_get_node(1);
    DEBUG_P("root used: %u", root.used);
//    DEBUG_P("root page: %u", root.page);
    Directory* rootDirectory = (Directory*) root.page;

    for (unsigned int i = 0; i < 20; i++) {
//        DEBUG_P("Index %u", i);
//        DirectoryEntry entry = rootDirectory->entries[i];
//        DEBUG_P("used: %u", rootDirectory->entries[i].used);
        if (rootDirectory->entries[i].used) {
            DEBUG_P("Name: %s", rootDirectory->entries[i].name);
        }
    }

    DEBUG_E(0);
    init_interrupt_controller();
    // enable_interrupt_controller();
    enable_irq();
    print("Hello, Raspberry pi\r\n");
    int64_t params[] = {(uint64_t)get_el()};
    printk("We are at EL %u\r\n", params);

    init_timer();
    // system_timer_init();
    DEBUG_F("init_timer();");

    int res = copy_process(PF_KTHREAD, (unsigned long)&kernel_process, 0, 0);
	if (res < 0) {
		print("error while starting kernel process");
		return;
	}

    // uint32_t res = copy_process((uint64_t)&process, (uint64_t)"12345");
    // DEBUG_P("process res: %u", res);
    // if (res != 0) {
    //     print("error while starting process 1");
    //     return;
    // }
    
    // res = copy_process((uint64_t)&process, (uint64_t)"abcde");
    // DEBUG_P("process res: %u", res);
    // if (res != 0) {
    //     print("error while starting process 2");
    //     return;
    // }

    while (1){
        schedule();
    }
}