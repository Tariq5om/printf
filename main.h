#ifndef MAIN_H
#define MAIN_H
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/**
 * struct special - the selector struct
 * @spe_char: The special character
 * @func: Point to function
 *
 * Description: Correspond the special character with it's function
*/
typedef struct special
{
	char *spe_char;
	char *(*func)();
} spe;
char *change_len(int *size_buf, char *pb, char **buffer, int len_buf);
char *p_string(char *pb, va_list *ar, int *size, char **buf, int len_buf);
char *_percent(char *pb, va_list *ar, int *size, char **buf, int len_buf);
int _strlen(char *str);
int _printf(const char *format, ...);
char *p_char(char *pb, va_list *ar, int *size, char **buf, int len_buf);
void *_realloc(void **ptr, unsigned int old_size, unsigned int new_size);
void ini_spes(spe **spes);
int sbuf(const char *f, char *pb, char **buf, int *size, va_list *ar, spe **s);
char *store_int(char *pb, va_list *ar, int *size, char **buf, int len_buf);
void store_dec(int n, char **pb, char **buf, int *size);
#endif/*endif*/
