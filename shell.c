#include "implicit_declarations_HQ.h"

#define APP argv[0]

int main(void)
{
	char *buf; /* Empty buffer for Getline to use */
	size_t len = 0; /* Getline will handle realloc */
	ssize_t bytes; /* Will stores bytes read by getline */
	char *program[64];
	int index;
	int status; /* Will store the status of execve */
	char *delimeter = " ";
	char *splitted;

	/* Get the inital dollar sign */
	printf("$ ");

	/* Getline reads (aka copies) everything from stdin into buf */
	/* @bytes: stores the number of chars reads */
	while((bytes = getline(&buf, &len, stdin)) > 0)
	{
		/* Check if getline failed */
		if (bytes == -1)
		{
			dprintf(STDERR_FILENO, "Unable to allocate memory\n");
			free(buf);
			exit(99);
		}
		/* splitting string */
		splitted = strtok(buf, delimeter);
		index = 0;
		while (splitted != NULL)
		{
			program[index] = splitted;
			printf("program[%d] = %s\n", index, program[index]);
			printf("splitted = %s\n", splitted);
			index++;

        		splitted = strtok(NULL, delimeter);
		}
		/* execute it */
		status = execve(program[0], program, NULL);
		if (status == -1)
		{
			dprintf(STDERR_FILENO, "%s: not found\n", program[0]);
		}
		/* Get the dollar sign for the the next prompt */
		printf("$ ");
	}
	free(*program);
	free(buf);
	return (0);
}
