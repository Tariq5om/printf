#include "main.h"

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
