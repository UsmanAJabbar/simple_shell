/**
 * charcheck - checks for whitespace input
 * takes it to main and stops it from executing
 * @str: string input
 * Return: -1 if Character's found | 0
 */
int charcheck(char *str)
{
	int index;

	if (_strncmp(str, " ", 1) == 0)
	{
		for (index = 0; str[index] != '\0'; index++)
		{
			if (str[index] != ' ')
				return (-1); /* Do you see a non-space now */
			; /* Else continue and check the next one */
		}
	}
	return (0);
}
