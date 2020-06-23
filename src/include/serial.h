extern unsigned int serial_enabled;
extern unsigned int serial_initialized;

#ifdef __cplusplus
#define OPT_EXTERN extern "C"
#else
#define OPT_EXTERN
#endif

OPT_EXTERN void serial_initialize();
OPT_EXTERN int serial_received();
OPT_EXTERN char serial_read();
OPT_EXTERN int serial_is_transmit_empty();
OPT_EXTERN void serial_putchar(char c);
OPT_EXTERN void serial_write(const char* data, size_t size);
OPT_EXTERN void serial_writestring(const char* data);
