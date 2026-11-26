/* debug.h */
#ifndef DEBUG_H
#define DEBUG_H

/* like printf but sends text out over USART2, using \r\n at the end of lines */
void debug_print(const char *fmt, ...);

#endif
