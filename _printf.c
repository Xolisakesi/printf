#include "main.h"
/**
 * _printf - function is used for formatted output
 * @format: the format string that specifies the
 * format of the output.
 * Return: returns the number of characters
 * printed if successful
 */
int _printf(const char *format, ...)
{
char *s, c;
int counter = 0;
va_list list;

if (!format)
return (-1);
va_start(list, format);
while (*format)
{
if (*format != '%')
wr_counter(format, counter);
else
{
format++;
if (*format == '\0')
break;
if (*format == '%')
wr_counter(format, counter);
else if (*format == 'c')
{
c = va_arg(list, int);
wr_counter(&c, counter);
}
else if (*format == 's')
{
s = va_arg(list, char*);
write(1, s, strlen(s));
counter += strlen(s);
}
}
format++;
}
va_end(list);
return (counter);
}
/**
 * wr_counter - writes a character and incrimens
 * a counter
 * @s: character to write
 * @incr: counter to be 8ncrimented
 * Return: void nothing
 */
void wr_counter(const char *s, int incr)
{
write(1, s, 1);
incr++;
}
