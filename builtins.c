#include "implicit_declaration_HQ.h"

/**
 * cd - changes the directory
 * @path: contains the destination path
 * Return: Returns the path
 */

int cd(char *path)
{
	return (chdir(path));
}

/**
 * echo - prints out whatever it recieves
 * @str: contains the string
 * Return: Always 0
 */
void *echo(char *str)
{
	if (str != NULL)
	{
		printf("%s", str);
	}
}

/**
  *
  *
  *
  *
  */
void *_ls(void)
{

}
