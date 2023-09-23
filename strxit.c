#include "simpshell.h"

/**
 **_strncpy - copies a string
 *@d: the destination string to be copied to
 *@s: the source string
 *@num: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dt, char *sr, int num)
{
	int i, j;
	char *st = dt;

	i = 0;
	while (sr[i] != '\0' && i < num - 1)
	{
		dt[i] = sr[i];
		i++;
	}
	if (i < num)
	{
		j = i;
		while (j < num)
		{
			dt[j] = '\0';
			j++;
		}
	}
	return (st);
}

/**
 **_strncat - concatenates two strings
 *@dt: the first string
 *@sr: the second string
 *@num: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dt, char *sr, int num)
{
	int i, j;
	char *st = dt;

	i = 0;
	j = 0;
	while (dt[i] != '\0')
		i++;
	while (sr[j] != '\0' && j < num)
	{
		dt[i] = sr[j];
		i++;
		j++;
	}
	if (j < num)
		dt[i] = '\0';
	return (st);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@m: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *str, char m)
{
	do {
		if (*str == m)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
