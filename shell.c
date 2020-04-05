#include "implicit_declarations_HQ.h"

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: int
 */
int main(void)
{
	char *args[64]; /* Array that would store argv inputs */
	char *splitted; /* Temp for each argv returned by strtok */
	char *buf; /* Empty buffer for Getline to use */
	size_t len = 0; /* Getline will handle realloc */
	int bytes, status; /* Will stores ? bytes (getline) | status of execve */
	int index;

	/* Get the inital dollar sign */
	printf("$ ");
	/* Getline reads (aka copies) everything from stdin into buf */
	while((bytes = getline(&buf, &len, stdin)) > 0)
	{
		/* Check if getline failed */
		if (bytes == -1)
			dprintf(STDERR_FILENO, "Unable to allocate memory\n"), free(buf), exit(95);

		/* Generate *argv[]s */
		splitted = strtok(buf, " ");
		for(index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");

		/* execute it */
		status = execve(args[0], args, NULL);
		if (status == -1)
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", args[0]); exit(96);

		/* Get the dollar sign for the the next prompt */
		printf("$ ");
	}
	return (0);
}
