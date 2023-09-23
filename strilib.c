#include "simpshell.h"

/**
 * _strcpy - copies a string
 * @d: the destination
 * @s: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *d, char *s)
{
	int i = 0;

	if (d == s || s == 0)
		return (d);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

/**
 * _strdup - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *s)
{
	int len = 0;
	char *dp;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	dp = malloc(sizeof(char) * (len + 1));
	if (!dp)
		return (NULL);
	for (len++; len--;)
		dp[len] = *--s;
	return (dp);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int j = 0;

	if (!s)
		return;
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char a)
{
	static int j;
	static char buffa[OUTPUT_BUFFER_SIZE];

	if (a == BUFFER_FLUSH || j >= OUTPUT_BUFFER_SIZE)
	{
		write(1, buffa, j);
		j = 0;
	}
	if (a != BUFFER_FLUSH)
		buffa[j++] = a;
	return (1);
}
