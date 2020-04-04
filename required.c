#include "implicit_declarations_HQ.h"
/**
 * splitter - splits strings into arrays
 * @str - input string
 * @delimiter - where to break the string
 * Return: individual words
 */

char **splitter(char *str, char *delimiter)
{
	char *array;
	char **word;
	int index;

	array = strtok(str, delimiter);
	/* Insert '\0' whenever it finds a delimiter */
	for (index = 0; array != NULL; index++)
	{
		/* Save the seperated word in the index */
		word[index] = array;

		/* Move to the next word in the string */
		array = strtok(NULL, delimiter);
	}
	word[index - 1] = '\0';
	return (word); /* Returns the word */
}
