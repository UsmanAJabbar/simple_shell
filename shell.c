#include "implicit_declarations_HQ.h"

#define FORK_F write(1, "Failed to fork PID\n", 20)
#define WAITPID waitpid(child, &pidstatus, WUNTRACED)
#define EXEC (execstatus = execve(args[0], args, NULL))
#define EXEC_F dprintf(STDERR_FILENO, "%s: not found\n", args[0])
#define PROMPT "$ "
#define CHILDSTATUS (child = fork())

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(int ac, char **av, char **env)
{
	char *args[64], *environment[100]; /* Array that would store argv inputs */
	char *in = NULL, *splitted; /* Buf for getline |Temp for each strtok argv*/
	size_t len = 0; /* Getline will handle realloc */
	int bytes, execstatus, index, pidstatus; /*Stores ? strlen|execstatus|index*/
	pid_t child; /* Generates and saves the child PID status */

	signal(SIGINT, ctrlc); /* Handles Ctrl-C Interrupt */
	while (1)
	{
		write(1, "initial $", 11); /* Get the inital dollar sign */

		/* Getline reads (aka copies) everything from stdin into input */
		if ((bytes = getline(&in, &len, stdin)) >= 0)
			in[bytes - 1] = '\0';
		else
			break;

		/* Generate *argv[]s */
		splitted = strtok(in, " ");
		for (index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");
		args[index] = NULL;

		if (_strncmp(args[0], "exit", 4)
			exit(0);

		/* Create a child process, execute it, reset status on fail */
		(CHILDSTATUS < 0) ? FORK_F : (child > 0) ? WAITPID : EXEC;
		if (execstatus < 0)
			EXEC_F, execstatus = 0;
	}
	write(1, "\n", 1), free(in), exit(pidstatus);
	return (0);
}
