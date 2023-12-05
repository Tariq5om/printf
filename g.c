#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
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

/**
 * change_len - change the length of buffer
 *
 * @size_buf: point to the last sace
 * @pb: last address
 * @buffer: The buffer
 * @len_buf: The length
 * Return: The new space
*/
char *change_len(int *size_buf, char *pb, char **buffer, int len_buf)
{
	int j;

	j = *size_buf;
	*buffer = _realloc((void **)buffer, j, *size_buf = 1024 + *size_buf);
	if (*buffer == NULL)
		return (NULL);
	pb = *buffer + len_buf;
	return (pb);
}
/**
 * _realloc - reallocate the memory block
 *
 * @ptr: the previously block
 * @old_size: the old_size of the block
 * @new_size: the new_size of the block
 * Return: the new block
*/
void *_realloc(void **ptr, unsigned int old_size, unsigned int new_size)
{
	void *poi;
	unsigned int j;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	poi = malloc(new_size);
	if (poi == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		if (new_size > old_size)
		{
			for (j = 0; j < old_size; j++)
				*((char *)poi + j) = *((char *)*ptr + j);
		}
		if (new_size < old_size)
		{
			for (j = 0; j < new_size; j++)
				*((char *)poi + j) = *((char *)*ptr + j);
		}
		if (new_size == old_size)
		{
			free(poi);
			return (*ptr);
		}
		free(*ptr);
	}
	return (poi);
}
/**
 * ini_spes - Initialize array of structures with format specifiers, functions
 *
 * @spes: Point to the array of structures
 * Return: void
*/
void ini_spes(spe **spes)
{
	/*Allocate for the array of structures*/
	*spes = malloc(sizeof(spe) * 4);

	if (*spes == NULL)
		return;
	/*Initialize array of structures with format specifiers & matching functions*/
	(*spes)[0].spe_char = "s";
	(*spes)[0].func = p_string;
	(*spes)[1].spe_char = "%";
	(*spes)[1].func = _percent;
	(*spes)[2].spe_char = "c";
	(*spes)[2].func = p_char;
	(*spes)[3].spe_char = "d";
	(*spes)[3].func = store_int;
	(*spes)[4].spe_char = "i";
	(*spes)[4].func = store_int;
	(*spes)[5].spe_char = NULL;
	(*spes)[5].func = NULL;

}
/**
 * sbuf - Store the formatted string in buffer
 *
 * @f: The formtted string
 * @pb: Pointer to buffer
 * @buf: The buffer
 * @size: The size of buffer
 * @ar: Pinter to the arguments list
 * @s: Pointer to array of structure
 * Return: int
*/
int sbuf(const char *f, char *pb, char **buf, int *size, va_list *ar, spe **s)
{
	int len_buf, i;

	for (; *f != '\0'; f++, pb++)
	{
		len_buf = pb - *buf;
		if (len_buf == *size - 1)
			pb = change_len(size, pb, buf, len_buf);
		if (*f == '%')
		{
			f++;
			for (i = 0; (*s)[i].spe_char; i++)
				if (*f == (*s)[i].spe_char[0])
				{
					pb = (*s)[i].func(pb, ar, size, buf, len_buf);
					break;
				}
			if (!(*s)[i].spe_char && *f != '\0')
			{
				*pb = *(--f);
				*(++pb) = *(++f);
			}
			else if (*f == '\0')
				return (-1);
		}
		else
			*pb = *f;
	}
	*pb = '\0';
	return (0);
}


/**
 * store_dec - print number
 *
 * @n: the number
 * @pb: Point to buffer
 * @buf: The buffer
 * @size: The size of buffer
 * Return: void
 */
void store_dec(int n, char **pb, char **buf, int *size)
{
	unsigned int nl;
	int len_buf;

	nl = n;
	if (n < 0)
	{
		(**pb) = '-';
		nl = -n;
		(*pb)++;
	}
	if (nl / 10 != 0)
	{
		store_dec(nl / 10, pb, buf, size);
	}
	**pb = ((nl % 10) + '0');
	(*pb)++;
	len_buf = *pb - *buf;/*To check if the buffer is full*/
		if (len_buf == *size - 1)
			*pb = change_len(size, *pb, buf, len_buf);
}
/**
 * store_int - Store int to buffer
 *
 * @pb: Pointer to buffer
 * @ar: The list of arguments
 * @size: pointer to size
 * @buf: Pointer to buffer
 * @len_buf: Check if buffer is full or not
 * Return: the next address
 */
char *store_int(char *pb, va_list *ar, int *size, char **buf, int len_buf)
{
	int n;

	(void)(len_buf);
	n = va_arg(*ar, int);
	store_dec(n, &pb, buf, size);
	return (--pb);
}

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
/**
 * main - Entry point
 *
 * Return: 0 on success, error code otherwise
 */
int main(void)
{
	int len, len2;

	len2 = printf("%d", 91024);
	len = _printf("%d", -1024);
	fflush(stdout);
	if (len != len2)
	{
		printf("\n%d\t%d", len2, len);
		printf("\nLengths differ.\n");
		fflush(stdout);
		return (1);
	}
	return (0);
}
