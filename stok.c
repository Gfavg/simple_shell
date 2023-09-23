#include "simpshell.h"

/**
 * **strtokk - splits a string into words. Repeat delimiters are ignored
 * @s: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtokk(char *st, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **sr;

	if (st == NULL || st[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; st[i] != '\0'; i++)
		if (!delim_ch(st[i], delim) && (delim_ch(st[i + 1], delim) || !st[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	sr = malloc((1 + numwords) * sizeof(char *));
	if (!sr)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (delim_ch(st[i], delim))
			i++;
		k = 0;
		while (!delim_ch(st[i + k], delim) && st[i + k])
			k++;
		sr[j] = malloc((k + 1) * sizeof(char));
		if (!sr[j])
		{
			for (k = 0; k < j; k++)
				free(sr[k]);
			free(sr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sr[j][m] = st[i++];
		sr[j][m] = 0;
	}
	sr[j] = NULL;
	return (sr);
}

/**
 * **strtokk1 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtokk1(char *st, char delim)
{
	int i, j, k, m, numwords = 0;
	char **sr;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != delim && st[i + 1] == delim) ||
		    (st[i] != delim && !st[i + 1]) || st[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	sr = malloc((1 + numwords) * sizeof(char *));
	if (!sr)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (st[i] == delim && st[i] != delim)
			i++;
		k = 0;
		while (st[i + k] != delim && st[i + k] && st[i + k] != delim)
			k++;
		sr[j] = malloc((k + 1) * sizeof(char));
		if (!sr[j])
		{
			for (k = 0; k < j; k++)
				free(sr[k]);
			free(sr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			sr[j][m] = st[i++];
		sr[j][m] = 0;
	}
	sr[j] = NULL;
	return (sr);
}
