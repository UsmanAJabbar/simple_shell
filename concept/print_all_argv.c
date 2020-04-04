#include <stdio.h>

int main(int argc __attribute((unused)), char *argv[])
{
	int i;

	/* While we don't get to the last argument */
	for (i = 0; argv[i] != NULL; i++)
	{
		/* continue printing all of argv */
		printf("%s\n", argv[i]);
	}

	return (0);
}
