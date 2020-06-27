
#ifndef STDDEF_H
#define STDDEF_H

#ifdef __cplusplus
#define OPT_EXTERN extern "C"
#else
#define OPT_EXTERN
#endif

typedef unsigned long size_t;
typedef long ptrdiff_t;

#endif
extern unsigned int serial_enabled;
extern unsigned int serial_initialized;

