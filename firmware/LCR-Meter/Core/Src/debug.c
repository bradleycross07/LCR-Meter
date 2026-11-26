/* debug.c */

/* includes */
#include "debug.h"
#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* defines */
#define DEBUG_BUF_SIZE        128  /* longest message, in characters */
#define DEBUG_UART_TIMEOUT_MS 100  /* max time to wait for the UART */

void debug_print(const char *fmt, ...)
{
	static char buf[DEBUG_BUF_SIZE];

	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);

	HAL_UART_Transmit(&huart2, (const uint8_t *)buf, strlen(buf), DEBUG_UART_TIMEOUT_MS);
}
