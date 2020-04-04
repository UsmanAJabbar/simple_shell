#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void)
{
	char *buf = NULL;
	size_t len = 0;
	size_t bytes;

	/** USAGE **/
	/* "$ " "Getline Function" */

	/* Get the inital dollar sign */
	printf("$ ");

	/* Check if getline got some input */
 	while(bytes = getline(&buf, &len, stdin) != '\0')
	{
		if (bytes == -1)
		{
			dprintf(STDERR_FILENO, "Unable to allocate memory\n");
			exit(99);
		}
		/* Echo whatever it got */
		printf("%s", buf);
		/* Get the dollar sign for the the next prompt */
		printf("$ ");
	}
	return (0);
}
