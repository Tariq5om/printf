#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
typedef struct iden
{
	char *s;
	char *(*fp)();
} id;
int _printf(const char *format, ...);
char *_str(char *buf, va_list *arg);
char *_mo(char *buf, va_list *arg);
int _strlen(char *s);
char *_char(char *buf, va_list *arg);
#endif/*endif*/
