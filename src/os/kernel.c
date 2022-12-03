#include "uart/uart.h"
#include "print/print.h"
#include "lib.h"
#include "debug/debug.h"
#include "timer/arm_timer.h"
#include "timer/system_timer.h"
#include "sysfc/fork.h"
#include "interrupt/gic400.h"
#include "sched/sched.h"
#include "filesystem/fat.h"
#include "user/terminal.h"
#include "sysproc/sysinfo.h"

static uint8_t path[1024];

void user_process1(char *array)
{
	char buf[2] = {0};
	while (1){
		for (int i = 0; i < 5; i++){
			buf[0] = array[i];
			call_sys_write(buf);
			delay(100000);
		}
	}
}

void register_process(unsigned long process) {
    unsigned long stack = call_sys_malloc();
    if (stack < 0) {
        print("Error while allocating stack for process 1\n\r");
        return;
    }
    int err = call_sys_clone(process, (unsigned long)"", stack);
    if (err < 0){
        print("Error while clonning process 1\n\r");
        return;
    }
}

void user_process(){
	char buf[30] = {0};
	print("User process started\n\r");
    // printp("Moved to EL %u\r\n", (uint64_t)get_el());
	print(buf);
	call_sys_write(buf);

    register_process((unsigned long)&terminal_main);
    register_process((unsigned long)&sysinfo_main);
//    register_process((unsigned long)mkdir);

//    unsigned long stack = call_sys_malloc();
//    if (stack < 0) {
//        print("Error while allocating stack for process 1\n\r");
//        return;
//    }
//    int err = call_sys_clone((unsigned long)&terminal_main, (unsigned long)"", stack);
//    if (err < 0){
//        print("Error while clonning process 1\n\r");
//        return;
//    }

//	unsigned long stack = call_sys_malloc();
//	if (stack < 0) {
//		print("Error while allocating stack for process 1\n\r");
//		return;
//	}
//	int err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"12345", stack);
//	if (err < 0){
//		print("Error while clonning process 1\n\r");
//		return;
//	}
//	stack = call_sys_malloc();
//	if (stack < 0) {
//		print("Error while allocating stack for process 1\n\r");
//		return;
//	}
//	err = call_sys_clone((unsigned long)&user_process1, (unsigned long)"abcd", stack);
//	if (err < 0){
//		print("Error while clonning process 2\n\r");
//		return;
//	}
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

//    Token * strings[32]
//    char strings[1024][32];
//    strsplitpath("/dev/home/admin", '/', *strings);
    char ** strings = strsplit("/dev/home/admin", '/', 1);
    for (int i = 0; i < 5; i++) {
        DEBUG_P("string: %s", strings + (i * 8 * 16));
    }

    Node root = fs_get_node(1);

//    straddtostart("/admin", path); //=> /admin
//    straddtostart("/home", path); //=> /home/admin
//    straddtostart("/root", path); //=> root/home/admnin
    // "/"
    DEBUG_P("ROOT PATH: %s", fs_get_path(root));

//    stradd2(path, "admin"); //=> /admin
//    stradd2(path, "home"); //=> /home/admin
//    stradd2(path, "root"); //=> root/home/admnin

//    char *s = straddtostart("/admin", "home", ch);
//    char *x = straddtostart(s, "root", path[1024]);
//    stradd2("admin", "/", path);
    // path = admin
   // stradd2(h, path);
    // Homeadmin
//    stradd2(path, "admin");
//    uint32_t len = strlen(path);
 //   DEBUG_P("ADDED: %s", path);

//    DEBUG_P("ADDED LEN: %u", strlen(path));
//    DEBUG_P("ADDED PATH: %s", path);
//    DEBUG_P("ADDED PATH2: %s", test2);
//    DEBUG_P("ADDED PATH3: %s", test3);

//    char * path = fs_get_path(root);
//    DEBUG_P("PATH: %s", path);

    Directory* rootDirectory = (Directory*) root.page;
    fs_create_directory(root, "test");
    rootDirectory->entries[5].node_id;

    for (uint32_t i = 0; i < 20; i++) {
        if (rootDirectory->entries[i].used) {
            DEBUG_P("Name: %s", rootDirectory->entries[i].name);
        }
    }
    Node node = fs_get_node(rootDirectory->entries[5].node_id);
    Directory * nodeDirectory = (Directory*) node.page;
    fs_create_file(node, "test2");
    // "/test"
    DEBUG_P("NODE PATH: %s", fs_get_path(node));
    for (uint32_t i = 0; i < 20; i++) {
        if (nodeDirectory->entries[i].used) {
            DEBUG_P("Name2: %s", nodeDirectory->entries[i].name);
        }
    }

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