#include "implicit_declarations_HQ.h"
#include <strings.h>

/**
 * _strcat - concats two strings
 * @dest: string to append to
 * @src: string to be appended to dest
 * Return: appended string
 */
char *_strcat(char *dest, char *src)
{
	int index, binlen = _strlen(dest);

	/* Copy everything from source into dest */
	for (index = 0; src[index] != '\0'; index++)
		/* src begins building on the last index of dest */
		dest[binlen + index] = src[index];
	return (dest);
}

/**
 * _strlen - calculates the string length
 * @string - string
 * Return: ? Return 0 if NULL | string length
 */
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

/**
 * _strncmp - compares two strings upto the limiter
 * @first: first string to compare
 * @second: second string to compare
 * @limit: number of first 'n' bytes to compare
 * Return: ? 0 if first = second : -1
 */
int _strncmp(char *first, char *second, int limit)
{
	int index;

	if (first != NULL && second != NULL)
		/* Compare as many indexes as limit limits */
		for (index = 0; index < limit; index++)
			if (first[index] == second[index])
				continue;
			else
				return (-1); /* Error unmatched character found */
	return (0); /* Both of the strings matches upto len defined by limit */
}

/* Take argv[0] to another function and append PATH env var to it */
/* This function should be able to accept ** and should return ** if */
/* argv[0] is an executable in any of the paths */
/* if argv[0] has a "./", do not append the path */
/* environ function is present in the header */


char *addpath(char *str)
{
	char *pathappended, *patharg, *pointer, *seppaths[32];
	int index, jindex, kindex;
	struct stat buffer;
	/* environ declared in header */

	if (str == NULL)
		return (NULL);

	/* if ./ is present in argv[0] return the original string */
	if (_strncmp(str, "./", 2) == 0)
		return (str); /* Returning a double pointer */

	/* Loop through environ until the first five characters are PATH= */
	for (index = 0; environ[index] != NULL; index++)
		if(_strncmp(environ[index], "PATH=", 5) == 0)
			break;


	/* Break the PATH= line into argvs */
	/* Continously save all possible paths into seppaths[]*/
	patharg = strtok(environ[index], ":");
	for (jindex = 0; patharg != NULL; jindex++)
		seppaths[jindex] = patharg, patharg = strtok(NULL, ":"), printf("seppaths tried: %s\n", seppaths[jindex]);
	seppaths[jindex] = NULL;
	pointer = strcat(seppaths[0], str);
	printf("Strcat appends: %s\n", pointer);

	/* Now that we're at PATH=[index], begin testing whether agrv[0] */
	/* is an executable in one of the paths */
	/* index through our seperated paths until one clicks! */
	for (kindex = 0; seppaths[kindex] != NULL; kindex++)
	{
		/* if ("PATH", "cmd") match  cat them and return the appended str */
		if (stat((_strcat(seppaths[kindex], str)), &buffer) == 0)
		{
			pathappended = _strcat(seppaths[kindex], str);
			printf("Catted String: %s\n", seppaths[kindex]);		
			return (pathappended); /* Returning a double pointer */
		}
		else
			continue;
	}
	pointer = strcat(seppaths[0], str);
	printf("Strcat appends2: %s\n", pointer);
	return (str);
}
