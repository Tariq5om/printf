#include "main.h"

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
