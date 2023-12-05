#include "main.h"
/**
 *
 * Return: 0 on success, error code otherwise
 */
int main(void)
{
	int len, len2;

	len2 = printf("%d", 91024);
	len = _printf("%d\n", -1024);
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
