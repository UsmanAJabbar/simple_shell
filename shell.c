#include "implicit_declarations_HQ.h"

#define FORK_F write(1, "Failed to fork PID\n", 20)
#define WAITPID waitpid(child, &pidstatus, WUNTRACED)
#define EXEC (status = execve(args[0], args, NULL))
#define EXEC_F dprintf(STDERR_FILENO, "%s: not found\n", args[0])
#define PROMPT "$ "

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(int argc, char *argv[], char *envp[])
{
	char *args[64]; /* Array that would store argv inputs */
	char *in = NULL, *splitted; /* Buf for getline |Temp for each strtok argv*/
	size_t len = 0; /* Getline will handle realloc */
	int bytes, status, index, pidstatus; /*Stores ? strlen | exec status | index*/
	pid_t child; /* Generates and saves the child PID status */

	signal(SIGINT, ctrlc); /* Handles Ctrl-C Interrupt */
	while (1)
	{
		write(1, "initial $", 11); /* Get the inital dollar sign */

		/* Getline reads (aka copies) everything from stdin into input */
		bytes = getline(&in, &len, stdin);
		in[bytes - 1] = '\0';

		/* Generate *argv[]s */
		splitted = strtok(in, " ");
		for (index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");
		args[index] = '\0';

		/* Create a child process, execute it, reset status on fail */
		((child = fork()) < 0) ? FORK_F : (child == 0) ? EXEC : WAITPID;
		if (status < 0)
			EXEC_F, status = 0;
	}
	return (0);
}
