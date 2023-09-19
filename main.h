#ifndef MAIN_H
#define MAIN_H


#include <stddef.h>
#include <stdio.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/* Macros */

#define PAD_RIGHT 1
#define PAD_ZERO 2
#define PRINT_BUF_LEN 1024

/* Function prototypes */

int _printf(const char *format, ...);
void printchar(char **str, int c);
int prints(char **out, const char *string, int width, int pad);
int printi(char **out, int i, int b, int sg, int width, int pad, int letbase);
int print(char **out, const char *format, va_list args);
int sprintf(char *out, const char *format, ...);

#endif
