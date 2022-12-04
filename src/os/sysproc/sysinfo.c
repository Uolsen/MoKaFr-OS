#include "user/terminal.h"
#include "sysfc/sys.h"
#include "print/print.h"
#include "uart/uart.h"
#include "stdlib/stdstring.h"
#include "debug/debug.h"

static uint64_t ticks = 0;

/**
 *
 */
void sysinfo_main()
{
	while (1)
	{
		ticks += 1;
		#ifdef DEBUG
			delay(10000);
		#else
			delay(1000);
		#endif
		// DEBUG_P("TICKS: %u", ticks);
	}
}

/**
 * Returns the current ticks.
 *
 * @return
 */
uint64_t sysinfo_get_ticks()
{
	return ticks;
}
