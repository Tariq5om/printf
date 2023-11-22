#include "main.h"

/**
 * _realloc - like realloc function
 *
 * @ptr: the last space
 * @old_size: old size of last block
 * @new_size: new size of new block
 * Return: new space
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *n;/*The new block*/
	unsigned int i;/*Loopcounter*/

	if (new_size == 0 && ptr != NULL)/*If it's not*/
	{
		free(ptr);
		return (NULL);
	}
	n = malloc(new_size);
	if (n == NULL)
		return (NULL);
	if (ptr != NULL)
	{
		if (new_size > old_size)
		{
			for (i = 0; i < old_size; i++)
				*((char *)n + i) = *((char *)ptr + i);
		}
		if (new_size < old_size)
		{
			for (i = 0; i < new_size; i++)
				*((char *)n + i) = *((char *)ptr + i);
		}
		if (new_size == old_size)
		{
			free(n);
			return (ptr);
		}
		free(ptr);/*free the last space*/
	}
	return (n);
}
