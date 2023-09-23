#include "simpshell.h"

/**
 * getEnv - returns the string array copy of our environ
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **getEnv(my_gf *gfav)
{
	if (!gfav->custom_environment || gfav->environment_changed)
	{
		gfav->custom_environment = list_2str(gfav->environment_list);
		gfav->environment_changed = 0;
	}

	return (gfav->custom_environment);
}

/**
 * unset_env - Remove an environment variable
 * @gfav: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_env(my_gf *gfav, char *var)
{
	my_list *node = gfav->environment_list;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = statWith(node->data, var);
		if (p && *p == '=')
		{
			gfav->environment_changed = delnode_n(&(gfav->environment_list), i);
			i = 0;
			node = gfav->environment_list;
			continue;
		}
		node = node->next_node;
		i++;
	}
	return (gfav->environment_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @gfav: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(my_gf *gfav, char *var, char *value)
{
	char *buf = NULL;
	my_list *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = gfav->environment_list;
	while (node)
	{
		p = statWith(node->data, var);
		if (p && *p == '=')
		{
			free(node->data);
			node->data = buf;
			gfav->environment_changed = 1;
			return (0);
		}
		node = node->next_node;
	}
	addNode_end(&(gfav->environment_list), buf, 0);
	free(buf);
	gfav->environment_changed = 1;
	return (0);
}
