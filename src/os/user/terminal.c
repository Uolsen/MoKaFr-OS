#include "user/terminal.h"
#include "sysfc/sys.h"
#include "print/print.h"
#include "uart/uart.h"
#include "stdlib/stdstring.h"
#include "debug/debug.h"
#include "sysproc/sysinfo.h"

static uint8_t input[MAX_BUFFER_SIZE];

void terminal_main()
{
	call_sys_write("Terminal started\r\n");
	call_sys_write("MoKaFrOS /:\r\n");
	// char input = read_char();
	printp("MoKaFrOS /: %s", input);

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

void programms(char * input){
	if (strncmp("ticks", input, strlen("ticks")) == 0){
		printp("TICKS: %u", sysinfo_get_ticks());
	} else {

	}
}

void terminal_clear()
{
	// clear input
	for (uint32_t i = 0; i < MAX_BUFFER_SIZE; i++)
	{
		input[i] = '\0';
	}

	// write new promt line
	call_sys_write("\r\n");
	printp("MoKaFrOS /: %s", input);
}
