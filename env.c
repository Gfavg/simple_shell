#include "simpshell.h"

/**
 * my_env - prints the current environment
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(my_gf *gfav)
{
	pr_list_ele(gfav->environment_list);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @gfav: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(my_gf *gfav, const char *name)
{
	my_list *node = gfav->environment_list;
	char *p;

	while (node)
	{
		p = statWith(node->data, name);
		if (p && *p)
			return (p);
		node = node->next_node;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @gfav: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_setenv(my_gf *gfav)
{
	if (gfav->argument_count != 3)
	{
		ePuts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(gfav, gfav->arg_values[1], gfav->arg_values[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_unsetenv(my_gf *gfav)
{
	int i;

	if (gfav->argument_count == 1)
	{
		ePuts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= gfav->argument_count; i++)
		unset_env(gfav, gfav->arg_values[i]);

	return (0);
}

/**
 * envList - populates env linked list
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int envList(my_gf *gfav)
{
	my_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNode_end(&node, environ[i], 0);
	gfav->environment_list = node;
	return (0);
}
