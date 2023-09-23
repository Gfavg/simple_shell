#include "simpshell.h"

/**
 * addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
my_list *addNode(my_list **head, const char *str, int num)
{
	my_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(my_list));
	if (!new_head)
		return (NULL);
	_setmem((void *)new_head, 0, sizeof(my_list));
	new_head->number = num;
	if (str)
	{
		new_head->data= _strdup(str);
		if (!new_head->data)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next_node = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addNode_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
my_list *addNode_end(my_list **head, const char *str, int num)
{
	my_list *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(my_list));
	if (!new_node)
		return (NULL);
	_setmem((void *)new_node, 0, sizeof(my_list));
	new_node->number = num;
	if (str)
	{
		new_node->data = _strdup(str);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next_node)
			node = node->next_node;
		node->next_node = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a my_list linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const my_list *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->data ? h->data : "(nil)");
		_puts("\n");
		h = h->next_node;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delnode_n(my_list **head, unsigned int index)
{
	my_list *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next_node;
		free(node->data);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next_node = node->next_node;
			free(node->data);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next_node;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(my_list **head_ptr)
{
	my_list *node, *next_n, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_n = node->next_node;
		free(node->data);
		free(node);
		node = next_n;
	}
	*head_ptr = NULL;
}
