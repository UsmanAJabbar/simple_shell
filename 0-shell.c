#include "implicit_declarations_HQ.h"

#define FORK_F		write(1, "Failed to fork PID\n", 20)
#define WAITPID		waitpid(child, &pidstatus, WUNTRACED)
#define EXEC		(execstatus = execve(addpath(args[0], "PATH="), args, environ))
#define EXEC_F		perror(args[0])
#define CHILDSTATUS	(child = fork())
#define GETLINE		(bytes = getline(&in, &len, stdin))
#define TOKENSEP " \t\n\v\r\a"
#define LOGIC_FILE (argv[1])
#define PASS 0xDEBAF

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(int argc, char *argv[])
{
	char *args[64]; /* Array that would store argv inputs */
	char *in = NULL, *tokens; /* Buf for getline |Temp for each strtok argv*/
	size_t len = 0; /* Getline will handle realloc */
	int bytes, execstatus, index, pidstatus, file_flag = 0; /*Stores?strlen|execstatus|[i]*/
	FILE *file = stdin;
	pid_t child; /* Generates and saves the child PID status */

	if (argc == 2)
	{
		file_flag = 1;
		if ((file = fopen(LOGIC_FILE, "r")) == NULL)
			dprintf(STDERR_FILENO, "Could not open file\n"), exit(99);
	}

	signal(SIGINT, ctrlc); /* Blocks Ctrl-C Exit */
	while (1)
	{
		(file_flag == 0) ? write(1, "$ ", 2) : PASS;
		/* Get the inital dollar sign */
		/* Getline reads (aka copies) everything from stdin into input */

		if ((bytes = getline(&in, &len, file)) < 0) break;
		else
			in[bytes - 1] = '\0';

		/* Generate *argv[]s */
		for (index = 0, tokens = strtok(in, TOKENSEP); tokens != NULL; index++)
			args[index] = tokens, tokens = strtok(NULL, TOKENSEP);
		args[index] = NULL;

		if (_strncmp(args[0], "exit", _strlen(args[0])) == 0)
			free(in), exit(0);
			
		(CHILDSTATUS < 0) ? FORK_F : (child > 0) ? WAITPID : EXEC;
		if (execstatus < 0) /* Did Exec Fail? Print fail statement */
			EXEC_F, execstatus = 0, free(in), exit(pidstatus);
	}
	(file_flag == 0) ? write(1, "\n", 1), free(in), exit(pidstatus) : PASS; /* Cleanup Getline Buffer */
	return (0);
}
