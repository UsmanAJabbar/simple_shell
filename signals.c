#include "implicit_declarations_HQ.h"

/**
 * ctrlc - void function that takes the singal interrupt (aka Ctrl-C)
 * and loads it onto the wrong plane
 * @name: the plane you throught boarded on
 * Return: Always Void
 * just like that luggage you're never getting back
 */
void ctrlc(int name)
{
	(void)name;
	write(1, "\n$ ", 1024);
}
