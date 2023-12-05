#include "main.h"

/**
 * _percent - Print the percent
 *
 * @pb: Pointer to buffer
 * @ar: The list of arguments
 * @size: pointer to size
 * @buf: Pointer to buffer
 * @len_buf: Check if buffer is full or not
 * Return: the next address
 */
char *_percent(char *pb, va_list *ar, int *size, char **buf, int len_buf)
{
	(void)(size);
	(void)(buf);
	(void)(len_buf);
	*pb = '%';
	(void)(ar);
	return (pb);
}
/**
 * _strlen - Calculate the length
 *
 * @str: a string
 * Return: Length
 */
int _strlen(char *str)
{
	int n;

	for (n = 0; str[n] != '\0'; n++)
		;
	return (n);
}
/**
 * p_char - Store a character in buffer
 *
 * @pb: Pointer to buffer
 * @ar: The list of arguments
 * @size: pointer to size
 * @buf: Pointer to buffer
 * @len_buf: Check if buffer is full or not
 * Return: the next address
 */
char *p_char(char *pb, va_list *ar, int *size, char **buf, int len_buf)
{
	char c;

	(void)(size);
	(void)(buf);
	(void)(len_buf);
	c = va_arg(*ar, int);
	if (c == '\0')
		c = '\a';
	*pb = c;
	return (pb);
}
/**
 * p_string - Store a string
 *
 * @pb: Pointer to buffer
 * @ar: The list of arguments
 * @size: pointer to size
 * @buf: Pointer to buffer
 * @len_buf: Check if buffer is full or not
 * Return: the next address
 */
char *p_string(char *pb, va_list *ar, int *size, char **buf, int len_buf)
{
	char *str;

	str = va_arg(*ar, char *);
	if (str == NULL)
		str = "(null)";
	for (; *str != '\0'; str++, pb++)
	{
		len_buf = pb - *buf;/*To check if the buffer is full*/
		if (len_buf == *size - 1)
			pb = change_len(size, pb, buf, len_buf);
		*pb = *str;
	}
	return (--pb);
}
/**
 * _printf - like printf
 *
 * @format: The not ready string
 * Return: The number of chataters
 */
int _printf(const char *format, ...)
{
	int i, j, size_buf;
	spe *spes;
	char *buffer, *ptrb;
	const char *ptrf;
	va_list ar;

	ptrf = format;
	if (!format)
		return (-1);

	size_buf = 1024;
	buffer = malloc(sizeof(char)  *  size_buf);
	if (buffer == NULL)
		return (0);
	ptrb = buffer;
	va_start(ar, format);
	ini_spes(&spes);/*Initialize the structure*/
	j = sbuf(ptrf, ptrb, &buffer, &size_buf, &ar, &spes);/*Store in the buffer*/
	if (j == -1)
		return (-1);
	write(1, buffer, i = _strlen(buffer));
	va_end(ar);
	free(spes);
	free(buffer);
	return (i);
}
