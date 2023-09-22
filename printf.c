#include "main.h"
/**
 * _printf - Custom printf function with format string support.                                                  * @format: The format string.                           * @...: Variable arguments.                             * Return: Number of characters printed.                 */

int _printf(const char *format, ...)
{
int result;
va_list args;
if(!format || '\0')
return (-1);
va_start(args, format);
result = print(NULL, format, args);
va_end(args);
return (result);
}
/**
 * printchar - Appends a character to a string or prints to stdout.
 * @str: Pointer to a string buffer or NULL for stdout.
 * @c: The character to append or print.
 */
void printchar(char **str, int c)
{
if (str)
{
**str = c;
++(*str);
}
else
(void)putchar(c);
}
/**
 * prints - Appends a string to a buffer with optional padding.
 * @out: Pointer to a string buffer.
 * @string: The string to append.
 * @width: Width of the field (padding).
 * @pad: Flag for zero padding.
 */
int prints(char **out, const char *string, int width, int pad)
{
int pc = 0;
char padchar = ' ';

if (width > 0)
{
int len = 0;
const char *ptr;
for (ptr = string; *ptr; ++ptr)
++len;
if (len >= width)
width = 0;
else
width -= len;
if (pad & PAD_ZERO)
padchar = '0';
}
if (!(pad & PAD_RIGHT))
{
while (width > 0)
{
printchar(out, padchar);
++pc;
--width;
}
}
while (*string)
{
printchar(out, *string++);
++pc;
}
while (width > 0)
{
printchar(out, padchar);
++pc;
--width;
}
return (pc);
}
/**
 * printi - Appends an integer to a buffer with base conversion and padding.
 * @out: Pointer to a string buffer.
 * @i: The integer to append.
 * @b: The base for conversion (e.g., 10 for decimal).
 * @sg: Sign flag (1 for signed, 0 for unsigned).
 * @width: Width of the field (padding).
 * @pad: Flag for zero padding.
 * @letbase: Base for letter digits (e.g., 'a' for hexadecimal).
 */
int printi(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
char print_buf[PRINT_BUF_LEN];
char *s;
int t, neg = 0, pc = 0;
unsigned int u = i;

if (i == 0)
{
print_buf[0] = '0';
print_buf[1] = '\0';
return (prints(out, print_buf, width, pad));
}
if (sg && b == 10 && i < 0)
{
neg = 1;
u = -i;
}
s = print_buf + PRINT_BUF_LEN - 1;
*s = '\0';
while (u)
{
t = u % b;
if (t >= 10)
{
t += letbase - '0' - 10;
}
*--s = t + '0';
u /= b;
}
if (b == 8)
{
if (width && (pad & PAD_ZERO))
{
printchar(out,'0');
++pc;
--width;
}
}
if (neg)
{
if (width && (pad & PAD_ZERO))
{
printchar(out, '-');
++pc;
--width;
}
else
*--s = '-';
}
return (pc + prints(out, s, width, pad));
}
/**
 * print - Custom print function with format string support.
 * @out: Pointer to a string buffer or NULL for stdout.
 * @format: The format string.
 * @args: Variable arguments list.
 *
 * Return: Number of characters written.
 */
int print(char **out, const char *format, va_list args)
{
/*extensive work still needs to be done here braking this function into more functions" functions.c" and a struct */
int width, pad;
int pc = 0;
const char *fmt = format;
char scr[2];

for (; *fmt; ++fmt)
{
if (*fmt == '%')
{
++fmt;
width = pad = 0;
if (*fmt == '\0') {
break;
}
if (*fmt == '%')
goto out;
if (*fmt == '-')
{
++fmt;
pad = PAD_RIGHT;
}
while (*fmt == '0')
{
++fmt;
pad |= PAD_ZERO;
}
for (; *fmt >= '0' && *fmt <= '9'; ++fmt)
{
width *= 10;
width += *fmt - '0';
}
if (*fmt == 's')
{
char *s = va_arg(args, char *);
pc += prints(out, s ? s : "(null)", width, pad);
continue;
}
if (*fmt == 'd' || *fmt == 'i')
{
pc += printi(out, va_arg(args, int), 10, 1, width, pad, 'a');
continue;
}
if (*fmt == 'x')
{
pc += printi(out, va_arg(args, int), 16, 0, width, pad, 'a');
continue;
}
if (*fmt == 'X')
{
pc += printi(out, va_arg(args, int), 16, 0, width, pad, 'A');
continue;
}
if (*fmt == 'u') {
pc += printi(out, va_arg(args, int), 10, 0, width, pad, 'a');
continue;
}
if (*fmt == 'c')
{
scr[0] = va_arg(args, int);
scr[1] = '\0';
pc += prints(out, scr, width, pad);
continue;
}
if (*fmt == 'o') {
pc += printi(out, va_arg(args, int), 8, 0, width, pad, 'a');
continue;
}
if (*fmt == 'p')
{
/* make a function here to Handle %p format specifier for pointers*/
void *address;
char addr_str[PRINT_BUF_LEN];
unsigned long addr_value, temp;
int i, digit, num_digits;;
address = va_arg(args, void *);
addr_value = (unsigned long)address;

addr_str[0] = '0';
addr_str[1] = 'x';
num_digits = 0;
temp = addr_value;
while (temp > 0)
{
temp /= 16;
num_digits++;
}
i = num_digits + 1;
while (addr_value != 0)
{
digit = addr_value % 16;
addr_str[i] = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
addr_value /= 16;
i--;
}
while (i > 1)
{
addr_str[i--] = '0';
}
addr_str[num_digits + 2] = '\0';
pc += prints(out, addr_str, width, pad);
continue;
}
if (*fmt == 'b') {
unsigned int b = va_arg(args, unsigned int);
pc += printi(out, b, 2, 0, width, pad, 'a');
continue;
}
if (*fmt == 'r')
{
int i;
char *str = va_arg(args, char *);
int len = strlen(str);
for (i = len - 1; i >= 0; i--)
{
printchar(out, str[i]);
++pc;
}
continue;
}
if (*fmt == 'R')
{
char c;
char *str = va_arg(args, char *);
int i, len = strlen(str);
for (i = 0; i < len; i++)
{
c = str[i];
if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
{
char base = (c >= 'a') ? 'a' : 'A';
printchar(out, (c - base + 13) % 26 + base);
}
else
{
printchar(out, c);
}
++pc;
}
continue;
}
if (*fmt == 'u') {
pc += printi(out, va_arg(args, int), 10, 0, width, pad, 'a');
continue;
}
if (*fmt == 'l') 
{
++fmt; 
if (*fmt == 'd' || *fmt == 'i') 
{
long int li = va_arg(args, long int);
pc += printi(out,li, 10, (li < 0), width, pad, 'a');
}
else if (*fmt == 'o') 
{
unsigned long int uli = va_arg(args, unsigned long int);
pc += printi(out, (int)uli, 8, 0, width, pad, 'a');
}
else if (*fmt == 'u') 
{
unsigned long int uli = va_arg(args, unsigned long int);
pc += printi(out, (int)uli, 10, 0, width, pad, 'a');
}
else if (*fmt == 'x' || *fmt == 'X') 
{
unsigned long int uli = va_arg(args, unsigned long int);
pc += printi(out, (int)uli, 16, 0, width, pad, (*fmt == 'X' ? 'A' : 'a'));
}
continue;
}

if (*fmt == 'h') 
{
++fmt; /* Move past 'h'*/
if (*fmt == 'd' || *fmt == 'i') {
short int hi = va_arg(args, int);
pc += printi(out, (int)hi, 10, (hi < 0), width, pad, 'a');
}
else if (*fmt == 'o') {
unsigned short int uhi = va_arg(args, unsigned int);
pc += printi(out, (int)uhi, 8, 0, width, pad, 'a');
}
else if (*fmt == 'u') 
{
unsigned short int uhi = va_arg(args, unsigned int);
pc += printi(out, (int)uhi, 10, 0, width, pad, 'a');
}
else if (*fmt == 'x' || *fmt == 'X') 
{
unsigned short int uhi = va_arg(args, unsigned int);
pc += printi(out, (int)uhi, 16, 0, width, pad, (*fmt == 'X' ? 'A' : 'a'));
}
/* Handle other format specifiers or modifiers as needed...*/
continue;
}

if (*fmt == 'S') {
char hex[5];
char *str = va_arg(args, char *);
int i, len = strlen(str);

for (i = 0; i < len; i++)
{
if ((str[i] < 32 || str[i] >= 127) && str[i] != '\0')
{
snprintf(hex, sizeof(hex), "\\x%02X", (unsigned char)str[i]);
pc += prints(out, hex, width, pad);
}
else
{
printchar(out, str[i]);
pc++;
}
}
continue;
}
if (*fmt == 'l' && *(fmt + 1) == 'd') {                 long d = va_arg(args, long);                            pc += printi(out, d, 10, 1, width, pad, 'a');           fmt++;                                                  continue;                                               }
printchar(out, '%');
printchar(out, *fmt);
pc += 2;

}
else
{
out:
printchar(out, *fmt);
++pc;
}
}
if (out)
**out = '\0';
return (pc);
}
/**
 * sprintf - Custom sprintf function with format string support.
 * @out: Pointer to the output string buffer.
 * @format: The format string.
 * @...: Variable arguments.
 * Return: Number of characters written.
 */
int sprintf(char *out, const char *format, ...)
{
int result;
va_list args;
va_start(args, format);
result = print(&out, format, args);
va_end(args);
return (result);
}
