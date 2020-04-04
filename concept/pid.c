#include <stdio.h>
#include <unistd.h>

/* Gets fetches and prints the process ID */

int main(void)
{
	/* Declaring a variable of type pid_t */
	pid_t child_pid;
	pid_t parent_pid;

	/* my_pid saves and returns the value returned by getpid */
	/* getpid doesn't have any parameters and is always void */
	child_pid = getpid();
	parent_pid = getppid();

	/* print the process ID returned by getpid */
	printf("The parent PID is %u\n", parent_pid);
	printf("The child PID is %u\n", child_pid);

	return (0);
}
