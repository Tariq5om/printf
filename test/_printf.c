#include "main.h"

/**
 * _strlen - length of string
 *
 * @s: The string
 * Return: The length
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}
/**
 * _mo - The modulo
 *
 * @buf: The buffer
 * @arg: The arguments
 * Return: the next address
 */
char *_mo(char *buf, va_list arg)
{
	(void)(arg);
	*buf = '%';
	return (++buf);
}
/**
 * _char - store character
 *
 * @buf: The buffer
 * @arg: The arguments
 * Return: the next address
 */
char *_char(char *buf, va_list arg)
{
	*buf = va_arg(arg, int);
	return (buf);
}
/**
 * _str - store string
 *
 * @buf: The buffer
 * @arg: The arguments
 * Return: the next address
 */
char *_str(char *buf, va_list arg)
{
	int i;
	char *s;

	s = va_arg(arg, char *);
	for (i = 0; s[i] != '\0'; i++)
		buf[i] = s[i];
	return (&buf[i - 1]);
}
/**
 * _printf - like printf
 *
 * @format: The formatted string
 * Return: number of chat displayed
 */
int _printf(const char *format, ...)
{
	va_list arg;
	id idd[] = {
		{"s", _str},
		{"%", _mo},
		{"c", _char},
		{NULL, NULL}
	};
	char *buffer, *pb;
	int i, len, size, j;

	size = 1024;
	buffer = malloc(sizeof(char)  *  size);
	if (buffer == NULL)
		return (0);
	pb = buffer;
	va_start(arg, format);
	for (; *format != '\0'; format++, pb++)
	{
		len = pb - buffer;
		if (len == size - 1)
		{
			j = size;
			buffer = _realloc(buffer, j, size = 1024 + size);
			if (buffer == NULL)
				return (0);
			pb = buffer + len;
		}
		if (*format == '%')
		{
			format++;
			for (i = 0; i < 3; i++)
			{
				if (*format == idd[i].s[0])
					pb = idd[i].fp(pb, arg);
			}
		}
		else
			*pb = *format;
	}
	*pb = '\0';
	write(1, buffer, i = _strlen(buffer));
	va_end(arg);
	free(buffer);
	return (i);
}
