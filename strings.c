#include "simpshell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *str)
{
	int j = 0;

	if (!str)
		return (0);

	while (*str++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * statWith - checks if chS starts with rootS
 * @rootS: string to search
 * @chS: the substring to find
 *
 * Return: address of next char of rootS or NULL
 */
char *statWith(const char *rootS, const char *chS)
{
	while (*chS)
		if (*chS++ != *rootS++)
			return (NULL);
	return ((char *)rootS);
}

/**
 * _strcat - concatenates two strings
 * @d: the destination buffer
 * @s: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *d, char *s)
{
	char *dp = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (dp);
}
