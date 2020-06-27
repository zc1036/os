#include <stddef.h>

#ifndef SERIAL_H
#define SERIAL_H 1

extern unsigned int serial_enabled;
extern unsigned int serial_initialized;

OPT_EXTERN void serial_initialize();
OPT_EXTERN int serial_received();
OPT_EXTERN char serial_read();
OPT_EXTERN int serial_is_transmit_empty();
OPT_EXTERN void serial_putchar(char c);
OPT_EXTERN void serial_write(const char* data, size_t size);
OPT_EXTERN void serial_writestring(const char* data);

#endif
