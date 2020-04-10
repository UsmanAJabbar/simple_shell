#include "implicit_declarations_HQ.h"
#include <strings.h>

/**
 * _strcatl - acts just like strcat except that
 * it adds both inputs into a new buffer, avoiding
 * the whole string literal dilemma
 * @dest: first input
 * @src: second input
 * Return: newstring | NULL
 */
char *_strcatl(char *dest, char *src)
{
	int index, jindex;
	char *newstring = malloc(_strlen(dest) + _strlen(src));

	if (dest == NULL || src == NULL)
	{
		free(newstring);
		return (NULL);
	}

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
char *addpath(char *cmd, char *envar)
{
	char *pathappended, *patharg, *seppaths[64], *fulldest, *slashcmd, *extractedenv;
	int index, jindex, kindex;
	struct stat buffer;
	/* environ declared in header */

	if (cmd == NULL)
	{
		free(cmd);
		return (NULL);
	}

	/* if ./ is present in argv[0] return the original string */
	if (_strncmp(cmd, "./", 2) == 0 || _strncmp(cmd, "/", 1) == 0)
		return (cmd);

	/* Loop through environ until the first five characters are PATH= */
	for (index = 0; environ[index] != NULL; index++)
		if(_strncmp(environ[index], envar, _strlen(envar)) == 0)
			break;

	/* Copy the full environment variable as a string */
	printf("Environ of index = %s\n", environ[index]);
	extractedenv = malloc(strlen(environ[index]) + 1);
	extractedenv = _strcatl("", environ[index]);
	/* extractedenv = environ[index]; */

	/* Break the PATH= line into argvs */
	/* Continously save all possible paths into seppaths[]*/
	patharg = strtok(extractedenv, ":");
	for (jindex = 0; patharg != NULL; jindex++)
		seppaths[jindex] = patharg, patharg = strtok(NULL, ":"), printf("seppaths[%d] has %s\n", jindex, seppaths[jindex]);
	seppaths[jindex] = NULL; /* Terminate seppaths array with NULL */

	/* Now that we're at PATH=[index], begin testing whether agrv[0] */
	/* is an executable in one of the paths */
	/* index through our seperated paths until one clicks! */
	slashcmd = _strcatl("/", cmd); /* Declaring outside the loop bec segfault */
	for (kindex = 0; seppaths[kindex] != NULL; kindex++)
	{
		fulldest = _strcatl(seppaths[kindex], slashcmd);
		printf("Looking for %s in %s\n", slashcmd, fulldest);
		/* if ("PATH", "cmd") match  cat them and return the appended str */
		if (stat(fulldest, &buffer) == 0)
		{
			pathappended = fulldest;
			printf("FOUND IT HERE: %s\n", pathappended);
			/* for (jindex = jindex - 1; jindex >= 0; jindex--)
			{
				printf("Cleanup\n");
				printf("Seppaths[%d] currently has %s\n", jindex, seppaths[jindex]);
				free(seppaths[jindex]);
				printf("After freeing Seppaths[%d] currently has %s\n", jindex, seppaths[jindex]);
			} */
			free(extractedenv);
			return (pathappended); /* Returning the appended string */
		}
	}
	printf("DIDN'T FIND IT ANYWHERE:\n");
	free(extractedenv);
	return (cmd);
}
