#include "user/terminal.h"
#include "sysfc/sys.h"
#include "print/print.h"
#include "uart/uart.h"
#include "stdlib/stdstring.h"

static uint8_t * input[MAX_BUFFER_SIZE];

void terminal_main()
{
	call_sys_write("Terminal started\n");
	call_sys_write("MoKaFrOS /:\n");
	// char input = read_char();
	printp("MoKaFrOS /: %s", input);

	while (1)
	{
		get_buffer(&input);
		
		printp("MoKaFrOS /: %s\n", input);

		delay(1000000000);
	}
}
