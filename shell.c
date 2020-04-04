#include "implicit_declarations_HQ.h"

#define APP argv[0]

int main(void)
{
	char *buf = malloc(512); /* Empty buffer for Getline to use */
	size_t len = 0; /* Getline will handle realloc */
	size_t bytes; /* Will stores bytes read by getline */
	char **program = malloc(512);
	int index = 0;
	int status; /* Will store the status of execve */

	/* Get the inital dollar sign */
	printf("$ ");

	/* Getline reads (aka copies) everything from stdin into buf */
	/* @bytes: stores the number of chars reads */
	while(bytes = getline(&buf, &len, stdin) > 0)
	{
		/* Check if getline failed */
		if (bytes == -1)
		{
			dprintf(STDERR_FILENO, "Unable to allocate memory\n");
			free(buf);
			exit(99);
		}
		/* split the string into argvs */
		while (index < 3)
		{
			program[index] = *splitter(buf, " ");
			index++;
		}
		/* execute it */
		execve(program[0], program, NULL);
		if (status = -1)
		{
			dprintf(STDERR_FILENO, "%s: not found/n", program[0]);
		}
		/* Get the dollar sign for the the next prompt */
		printf("$ ");
	}
	return (0);
}
