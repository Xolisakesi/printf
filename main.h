#ifndef MAIN_H
#define MAIN_H

/* Header files */

#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/* function prototypes */
int _printf(const char *format, ...);
void wr_counter(const char *s, int *incr);

#endif
