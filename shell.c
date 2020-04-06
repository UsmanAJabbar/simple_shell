#include "implicit_declarations_HQ.h"
#define FORK_F printf("Failed to fork PID\n")
#define WAITPID waitpid(child, &pidstatus, WUNTRACED)
#define EXEC (status = execve(args[0], args, NULL))
#define EXEC_F dprintf(STDERR_FILENO, "%s: not found\n", args[0])

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(void)
{
	char *args[64]; /* Array that would store argv inputs */
	char *buf = NULL, *splitted; /* Buf for getline | Temp for each strtok argv */
	size_t len = 0; /* Getline will handle realloc */
	int bytes, status, index, pidstatus; /*Stores ? strlen | exec status | index*/
	pid_t child; /* Generates and saves the child PID status */

	printf("$ "); /* Get the inital dollar sign */
	/* Getline reads (aka copies) everything from stdin into buf */
	while ((bytes = getline(&buf, &len, stdin)) > 0)
	{
		buf[bytes - 1] = '\0'; /* Replaces /n with '\0' */

		/* Generate *argv[]s */
		splitted = strtok(buf, " ");
		for (index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");
		args[index] = '\0';

		/* Create a child process, execute it, reset status on fail */
		((child = fork()) < 0) ? FORK_F : (child == 0) ? EXEC : WAITPID;
		(status < 0) ? EXEC_F, printf("$ "), status = 0 : printf("$ ");
	}
	return (0);
}
