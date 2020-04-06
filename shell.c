#include "implicit_declarations_HQ.h"
#define FORK_F write(1,"Failed to fork PID\n", 20)
#define WAITPID waitpid(child, &pidstatus, WUNTRACED)
#define EXEC (status = execve(args[0], args, NULL))
#define EXEC_F dprintf(STDERR_FILENO, "%s: not found\n", args[0])
#define PROMPT "$ "

void func(int name)
{
	(void)name;
	printf("\n$ ");
}

/**
 * main - a simple shell program that
 * runs user inputs, parses, and executes them
 * Return: - Always 0
 */
int main(void)
{
	char *args[64]; /* Array that would store argv inputs */
	char *input = NULL, *splitted; /* Buf for getline | Temp for each strtok argv */
	char bin[] = "/bin/";
	size_t len = 0; /* Getline will handle realloc */
	int bytes, status, index, pidstatus; /*Stores ? strlen | exec status | index*/
	pid_t child; /* Generates and saves the child PID status */

	write(1, "initial $", 11); /* Get the inital dollar sign */
	signal(SIGINT, func);
	/* Getline reads (aka copies) everything from stdin into input */
	while ((bytes = getline(&input, &len, stdin)) > 0)
	{
		char bin[] = "/bin/";
		input[bytes - 1] = '\0'; /* Replaces /n with '\0' */

		printf("Before strcmp/cat getline copied %d bytes into input\n", bytes);

		/* Cat if input has doesn't have /bin/ present ahead of it */
		if(_strncmp(bin, input, _strlen(bin)) != 0)
			_strcat(bin, input);

		printf("Bin has: %s\n", bin);

		/* Generate *argv[]s */
		splitted = strtok(bin, " ");
		for (index = 0; splitted != NULL; index++)
			args[index] = splitted, splitted = strtok(NULL, " ");
		args[index] = '\0';
		/* Create a child process, execute it, reset status on fail */
		((child = fork()) < 0) ? FORK_F : (child == 0) ? EXEC : WAITPID;
		(status < 0) ? EXEC_F, write(1, PROMPT, 3), status = 0, _memset(bin, 0, sizeof(bin)) : write(1, PROMPT, 3), _memset(bin, 0, sizeof(bin));

	}
	return (0);
}
