#include "simpshell.h"

/**
 * len_list - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t len_list(const my_list *a)
{
	size_t i = 0;

	while (a)
	{
		a = a->next_node;
		i++;
	}
	return (i);
}

/**
 * list_2str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_2str(my_list *head)
{
	my_list *node = head;
	size_t i = len_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next_node, i++)
	{
		str = malloc(_strlen(node->data) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->data);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * pr_list - prints all elements of a my_list linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t pr_list(const my_list *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(conv_numb(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->data ? h->data : "(nil)");
		_puts("\n");
		h = h->next_node;
		i++;
	}
	return (i);
}

/**
 * node_starts - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
my_list *node_starts(my_list *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = statWith(node->data, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next_node;
	}
	return (NULL);
}

/**
 * getNode_n - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNode_n(my_list *head, my_list *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next_node;
		i++;
	}
	return (-1);
}
