#include "user/terminal.h"
#include "sysfc/sys.h"
#include "print/print.h"
#include "uart/uart.h"

void terminal_main()
{
	call_sys_write("Terminal started\n");
	call_sys_write("MoKaFrOS /:\n");
	char input = read_char();
	printp("MoKaFrOS /: %s", input);

	while (1)
	{
		char * buff = get_buffer();
		printp("MoKaFrOS /: %s\n", buff);

		delay(1000000000);
	}
}
