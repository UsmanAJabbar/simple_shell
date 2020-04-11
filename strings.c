#include "implicit_declarations_HQ.h"
#include <strings.h>

/**
 * _strcatl - acts just like strcat except that
 * it adds both inputs into a new buffer, avoiding
 * the whole string literal dilemma
 * @dest: first input
 * @src: second input
 * Return: Return's malloc'ed newstring | NULL
 */
char *_strcatl(char *dest, char *src)
{
	int index, jindex;
	char *newstring = malloc(_strlen(dest) + _strlen(src) + 1);

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

/**
 * addpath - takes in a string and searches for
 * cmd in aforementioned environment variable
 * @cmd: string with program to search for in
 * environment variables.
 * @envar: string with environment variable
 * to search in.
 * Return: Returns cmd with the path appended
 * to it.
 */
char *addpath(char *cmd, char *envar)
{
	char *patharg, *seppaths[64], *fulldest, *slashcmd, *extractedenv;
	int index, jindex, kindex;
	struct stat buffer;
	/* environ declared in header */

	if (cmd == NULL)
		return (NULL);
	/* if ./ is present in argv[0] return the original string */
	if (_strncmp(cmd, "./", 2) == 0 || _strncmp(cmd, "/", 1) == 0)
		return (cmd);

	/* Loop through environ until environment variable's found */
	for (index = 0; environ[index] != NULL; index++)
		if(_strncmp(environ[index], envar, _strlen(envar)) == 0)
			break;

	/* Copy the full environment variable as a string */
	extractedenv = _strcatl("", environ[index]);

	/* Break the PATH= line into argvs */
	for (jindex = 0, patharg = strtok(extractedenv, ":"); patharg != NULL; jindex++)
		seppaths[jindex] = patharg, patharg = strtok(NULL, ":"), printf("seppaths[%d] has %s\n", jindex, seppaths[jindex]);
	seppaths[jindex] = NULL; /* Terminate seppaths array with NULL */

	/* index through our seperated paths until one clicks! */
	for (kindex = 0, slashcmd = _strcatl("/", cmd); seppaths[kindex] != NULL; kindex++)
	{
		fulldest = _strcatl(seppaths[kindex], slashcmd);
		printf("Looking for %s in %s\n", slashcmd, fulldest);
		/* if cmd+path match and is evecutable, return the string */
		if (stat(fulldest, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
		{
			printf("FOUND IT HERE: %s\n", fulldest);
			free(extractedenv);
			return (fulldest); /* Returning the appended string */
		}
	}
	printf("DIDN'T FIND IT ANYWHERE:\n");
	free(extractedenv);
	return (cmd);
}
