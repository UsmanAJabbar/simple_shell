#include "implicit_declarations_HQ.h"

#define FORK_F write(1, "Failed to fork PID\n", 20)
#define WAITPID waitpid(child, &pidstatus, WUNTRACED)
#define EXEC (execstatus = execve(addpath(args[0], "PATH="), args, environ))
#define EXEC_F perror(argv[0])
#define CHILDSTATUS (child = fork())
#define GETLINE (bytes = getline(&in, &len, stdin))
#define TOKENSEP " \t\n\v\r\a"
/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * @argc: argument count
 * @argv: argument vector - used for perror for EXEC_F
 * Return: - Always 0
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char *args[64]; /* Array that would store argv inputs */
	char *in = NULL, *tokens; /* Buf for getline |Temp for each strtok argv*/
	size_t len = 0; /* Getline will handle realloc */
	int bytes, execstatus = 0, index, pidstatus; /*Stores?strlen|execstatus|[i]*/
	pid_t child; /* Generates and saves the child PID status */
	int isinteractive = 0;

	signal(SIGINT, ctrlc); /* Blocks Ctrl-C Exit */

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2); /* Get the inital dollar sign */
		else
			isinteractive = -1;

		GETLINE;/* Bytes < 0 + Isinteractive = 0 */
		/* Ctrl-D pushes the PS1 to the next line */
		if (bytes < 0 && isinteractive == 0)
			write(1, "\n", 1), free(in), exit(0);
		else if (bytes < 0 && isinteractive == -1)
			free(in), exit(0);
		else
			in[bytes - 1] = '\0';

		/* Check if in captured "exit" */
		if (_strncmp(in, "exit", 4) == 0)
			free(in), exit(0);

		/* Generate *argv[]s */
		for (index = 0, tokens = strtok(in, TOKENSEP); tokens != NULL; index++)
			args[index] = tokens, tokens = strtok(NULL, TOKENSEP);
		args[index] = NULL;

		/* Create a child process, execute it, reset status on fail */
		/* If child returns -1, Fork Failed, Else if Child > 0, Wait */
		/* The only case left is when child = 0, then execute */
		(CHILDSTATUS < 0) ? FORK_F : (child > 0) ? WAITPID : EXEC;
		if (execstatus < 0) /* Did Exec Fail? Print fail statement */
			EXEC_F, execstatus = 0, free(in), exit(pidstatus);
		if (isinteractive == -1)
			free(in), exit(0);
	}
	/* write(1, "\n", 1), */ free(in), exit(pidstatus); /* Cleanup Getline Buffer */
	return (0);
}
