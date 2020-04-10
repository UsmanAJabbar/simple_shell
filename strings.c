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
 * newcat - acts just like strcat
 * except that it adds both inputs
 * into a new buffer
 * @dest: first input
 * @src: second input
 * Return: newstring | NULL
 */
char *newcat(char *dest, char *src)
{
	int index, jindex;
	char *newstring = malloc(_strlen(dest) + _strlen(src));

	if (dest == NULL || src == NULL)
		return (NULL);

	/* Fill in newstring with dest */
	for (index = 0; dest[index] != '\0'; index++)
		newstring[index] = dest[index];

	/* Add src to the same buffer */
	for (jindex = 0; src[jindex] != '\0'; jindex++, index++)
		newstring[index] = src[jindex];

	return (newstring);
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
	char *pathappended, *patharg, *seppaths[32], *fulldest, *slashcmd;
	int index, jindex, kindex;
	struct stat buffer;
	/* environ declared in header */

	if (str == NULL)
		return (NULL);

	/* if ./ is present in argv[0] return the original string */
	if (_strncmp(str, "./", 2) == 0 || _strncmp(str, "/", 1) == 0)
		return (str);

	/* Loop through environ until the first five characters are PATH= */
	for (index = 0; environ[index] != NULL; index++)
		if(_strncmp(environ[index], "PATH=", 5) == 0)
			break;

	/* Break the PATH= line into argvs */
	/* Continously save all possible paths into seppaths[]*/
	patharg = strtok(environ[index], ":");
	for (jindex = 0; patharg != NULL; jindex++)
		seppaths[jindex] = patharg, patharg = strtok(NULL, ":"), printf("strok divided: %s\n", seppaths[jindex]);
	seppaths[jindex] = NULL;

	/* Now that we're at PATH=[index], begin testing whether agrv[0] */
	/* is an executable in one of the paths */
	/* index through our seperated paths until one clicks! */
	slashcmd = newcat("/", str); /* Declaring outside the loop bec segfault */
	for (kindex = 0; seppaths[kindex] != NULL; kindex++)
	{
		fulldest = newcat(seppaths[kindex], slashcmd);
		printf("Looking for %s in %s\n", slashcmd, fulldest);
		/* if ("PATH", "cmd") match  cat them and return the appended str */
		if (stat(fulldest, &buffer) == 0)
		{
			pathappended = fulldest;
			printf("FOUND IT HERE: %s\n", pathappended);
			return (pathappended); /* Returning a double pointer */
		}
	}
	printf("DIDN'T FIND IT ANYWHERE: %s\n", fulldest);
	return (str);
}
