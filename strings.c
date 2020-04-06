#include "implicit_declarations_HQ.h"

char *_strcat(char *dest, char *src)
{
	int index, binlen = _strlen(dest);

	/* Copy everything from source into dest */
	for (index = 0; src[index] != '\0'; index++)
		/* src begins building on the last index of dest */
		dest[binlen + index] = src[index];
	return (dest);
}

int _strlen(char *string)
{
	int index;

	/* Check if string is not null */
	if (string != NULL)
	{
		for (index = 0; string[index] != '\0'; index++)
			;
		return (index);
	}
	return (0); /* If it is null */
}

int _strncmp(char *first, char *second, int limit)
{
	int index;

	if (first != NULL && second != NULL)
	{
		/* Compare as many indexes as limit limits */
		for (index = 0; index < limit; index++)
		{
			if (first[index] == second[index])
				continue;
			else
				return (-1); /* Error unmatched character found */
		}
	}
	return (0); /* Both of the strings matches upto len defined by limit */
}
/**
 * _memset - takes value from pointer s
 * replaces with values from b
 * @b: var that needs to be replaced
 * @n: number of bytes/characters to be reassigned
 * @s: pointer contains value stored in s.
 * Return: Returns new value to pointer s
 */
char *_memset(char *s, char b, unsigned int n)
{
	char *r = s;

	while (n > 0)
	{
		*s = b;
		s++;
		n--;
	}

return (r);
}
