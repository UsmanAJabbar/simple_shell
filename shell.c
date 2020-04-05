#include "implicit_declarations_HQ.h"

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(void)
{
	char *args[64]; /* Array that would store argv inputs */
	char *splitted; /* Temp for each argv returned by strtok */
	char *buf; /* Empty buffer for Getline to use */
	size_t len = 0; /* Getline will handle realloc */
	int bytes, status, index; /*Stores ? bytes (getline) | execve status | index*/

	printf("$ "); /* Get the inital dollar sign */
	/* Getline reads (aka copies) everything from stdin into buf */
	while ((bytes = getline(&buf, &len, stdin)) > 0)
	{
		if (bytes == -1) /* Check if getline failed */
			dprintf(STDERR_FILENO, "Unable to enter the shell\n"), free(buf), exit(95);
		buf[bytes - 1] = '\0'; /* Replaces /n with '\0' */

		/* Generate *argv[]s */
		splitted = strtok(buf, " ");
		for (index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");
		args[index] = '\0';

		/* execute it */
		status = execve(args[0], args, NULL); /* Save int return from execve */
		if (status == -1) /* Check if execve failed */
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", args[0]), exit(96);

		/* Get the dollar sign for the the next prompt */
		printf("$ ");
	}
	return (0);
}
