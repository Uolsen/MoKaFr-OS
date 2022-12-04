#include "user/terminal.h"
#include "sysfc/sys.h"
#include "print/print.h"
#include "uart/uart.h"
#include "stdlib/stdstring.h"
#include "debug/debug.h"
#include "rng/prng.h"
#include "sysproc/sysinfo.h"
#include "user/fs_terminal.h"
#include "filesystem/fat.h"

static uint8_t input[MAX_BUFFER_SIZE];

static uint32_t current_node_id;

/**
 * Returns the currently visited (filesystem) node.
 * @return
 */
uint32_t get_current_node_id() {
    return current_node_id;
}

/**
 * Entry point of the terminal process.
 */
void terminal_main()
{
    current_node_id = 1;
	call_sys_write("Terminal started\r\n");
	call_sys_write("MoKaFrOS /:\r\n");
	// char input = read_char();
//	printp("MoKaFrOS /: %s", input);
    int64_t params[] = {fs_get_path(fs_get_node(current_node_id)), input};
    printk("MoKaFrOS %s: %s", params);

	uint8_t state = term_input;

	while (1)
	{

		switch (state)
		{
		case term_input:
			terminal_reading();
			break;
		default:
			break;
		}
	}
}

/**
 * Reading UART input for terminal.
 */
void terminal_reading()
{
	static uint8_t *buffer[MAX_BUFFER_SIZE];
	get_buffer(&buffer);

	stradd(input, buffer, strlen(buffer));

	printp("%s", buffer);

	uint32_t inp_len = strlen(input);
	if (inp_len > 2)
	{

		if (input[inp_len - 1] == '\n' && input[inp_len - 2] == ';')
		{
			terminal_clear();
		}
		else if (input[inp_len - 1] == '\n')
		{
			// work with input
			printp("WORKING WITH: %s", input);

			programms(input);

			terminal_clear();
		}
	}

	delay(10000);
}

/**
 * Handles all terminal programmes.
 *
 * @param input Input of the CLI
 */
void programms(char * input) {
    if (strncmp("ticks", input, strlen("ticks")) == 0) {
        printp("Ticks: %u", sysinfo_get_ticks());
    } else if (strncmp("rand", input, strlen("rand")) == 0) {
        printp("Random number: %u", prng_get());
    } else if (strncmp("mkdir", input, strlen("mkdir")) == 0) {
        mkdir(input);
    } else if (strncmp("ls", input, strlen("ls")) == 0) {
        ls();
    } else if (strncmp("cd", input, strlen("cd")) == 0) {
        current_node_id = cd(current_node_id, input);
    } else if (strncmp("pwd", input, strlen("pwd")) == 0) {
        pwd();
    } else if (strncmp("touch", input, strlen("touch")) == 0) {
        touch(input);
    } else if (strncmp("cat", input, strlen("cat")) == 0) {
        cat(input);
    } else if (strncmp("test", input, strlen("test")) == 0) {
        DEBUG_P("GFX PIPE addr: %x", get_gfx_pipe());
        fs_pread(get_gfx_pipe());
        fs_fread(get_gfx_pipe(), 32);
    } else if (strncmp("draw", input, strlen("draw")) == 0) {
        draw(input);
    }
}

/**
 * Clears the terminal input.
 */
void terminal_clear()
{
	// clear input
	for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
	{
		input[i] = '\0';
	}

	// write new prompt line
	call_sys_write("\r\n");
//	printp("MoKaFrOS /: %s", input);
    int64_t params[] = {fs_get_path(fs_get_node(current_node_id)), input};
    printk("MoKaFrOS %s: %s", params);
}
