#include "simpshell.h"

/**
 *ePuts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void ePuts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		ePutchar(str[i]);
		i++;
	}
}

/**
 * ePutchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int ePutchar(char c)
{
	static int i;
	static char buffa[OUTPUT_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= OUTPUT_BUFFER_SIZE)
	{
		write(2, buffa, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffa[i++] = c;
	return (1);
}

/**
 * Putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int Putfd(char c, int fd)
{
	static int i;
	static char buffa[OUTPUT_BUFFER_SIZE];

	if (c == BUFFER_FLUSH || i >= OUTPUT_BUFFER_SIZE)
	{
		write(fd, buffa, i);
		i = 0;
	}
	if (c != BUFFER_FLUSH)
		buffa[i++] = c;
	return (1);
}

/**
 *Putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int Putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += Putfd(*str++, fd);
	}
	return (i);
}
