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

char *addbin(char *str)
{
	char *newstring;
	char *bin = "/bin/";
	int index, jindex;

	if (str == NULL)
	{
		perror("String's empty\n");
		return (NULL);
	}

	/* Copying /bin/ into the new string */
	for (index = 0; bin[index] != '\0'; index++)
		newstring[index] = bin[index];

	/* Cat argv[0] into the new string */
	for (jindex = 0; str[jindex] != '\0'; index++, jindex++)
		newstring[index] = str[jindex];

	return (newstring);
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
