#include "simpshell.h"

/**
 * my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @gfav: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(my_gf *gfav)
{
	pr_list(gfav->history_data);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @gfav: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(my_gf *gfav, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delnode_n(&(gfav->alias_data),
		getNode_n(gfav->alias_data, node_starts(gfav->alias_data, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @gfav: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(my_gf *gfav, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(gfav, str));

	unset_alias(gfav, str);
	return (addNode_end(&(gfav->alias_data), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(my_list *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->data, '=');
		for (a = node->data; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(my_gf *gfav)
{
	int i = 0;
	char *p = NULL;
	my_list *node = NULL;

	if (gfav->argument_count == 1)
	{
		node = gfav->alias_data;
		while (node)
		{
			print_alias(node);
			node = node->next_node;
		}
		return (0);
	}
	for (i = 1; gfav->arg_values[i]; i++)
	{
		p = _strchr(gfav->arg_values[i], '=');
		if (p)
			set_alias(gfav, gfav->arg_values[i]);
		else
			print_alias(node_starts(gfav->alias_data, gfav->arg_values[i], '='));
	}

	return (0);
}
