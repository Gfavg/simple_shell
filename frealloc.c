#include "simpshell.h"

/**
 **_setmem - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@val: the byte to fill *s with
 *@num: the amount of bytes to be filled
 *Return: (str) a pointer to the memory area str
 */
char *_setmem(char *str, char val, unsigned int num)
{
	unsigned int j;

	for (j = 0; j < num; j++)
		str[j] = val;
	return (str);
}

/**
 * freee - frees a string of strings
 * @s: pointer to pointer
 */
void freee(char **s)
{
	char **c = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(c);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @cur_size: byte size of previous block
 * @n_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int cur_size, unsigned int n_size)
{
	char *a;

	if (!ptr)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr), NULL);
	if (n_size == cur_size)
		return (ptr);

	a = malloc(n_size);
	if (!a)
		return (NULL);

	cur_size = cur_size < n_size ? cur_size : n_size;
	while (cur_size--)
		a[cur_size] = ((char *)ptr)[cur_size];
	free(ptr);
	return (a);
}
