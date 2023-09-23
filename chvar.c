#include "simpshell.h"

/**
 * isit_chain - test if current char in buffer is a chain delimeter
 * @gfav: the parameter struct
 * @buf: the character buffer
 * @p: current position in buffer address
 *
 * Return: 1 if it is chain delim, 0 if not
 */
int isit_chain(my_gf *gfav, char *buffa, size_t *add)
{
	size_t i = *add;

	if (buffa[i] == '|' && buffa[i + 1] == '|')
	{
		buffa[i] = 0;
		i++;
		gfav->command_buffer_type = COMMAND_LOGICAL_OR;
	}
	else if (buffa[i] == '&' && buffa[i + 1] == '&')
	{
		buffa[i] = 0;
		i++;
		gfav->command_buffer_type = COMMAND_LOGICAL_AND;
	}
	else if (buffa[i] == ';') /* found end of this command */
	{
		buffa[i] = 0; /* replace semicolon with null */
		gfav->command_buffer_type = COMMAND_CHAINED;
	}
	else
		return (0);
	*add = i;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @gfav: the parameter struct
 * @buffa: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @length: length of buf
 *
 * Return: Void
 */
void ch_chain(my_gf *gfav, char *buffa, size_t *add, size_t i, size_t length)
{
	size_t k = *add;

	if (gfav->command_buffer_type == COMMAND_LOGICAL_AND)
	{
		if (gfav->execution_status)
		{
			buffa[i] = 0;
			k = length;
		}
	}
	if (gfav->command_buffer_type == COMMAND_LOGICAL_OR)
	{
		if (!gfav->execution_status)
		{
			buffa[i] = 0;
			k = length;
		}
	}

	*add = k;
}

/**
 * rpl_alias - replaces an aliases in the tokenized string
 * @gfav: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rpl_alias(my_gf *gfav)
{
	int i;
	my_list *Newnode;
	char *p;

	for (i = 0; i < 10; i++)
	{
		Newnode = node_starts(gfav->alias_data, gfav->arg_values[0], '=');
		if (!Newnode)
			return (0);
		free(gfav->arg_values[0]);
		p = _strchr(Newnode->data, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		gfav->arg_values[0] = p;
	}
	return (1);
}

/**
 * rpl_vars - replaces vars in the tokenized string
 * @gfav: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rpl_vars(my_gf *gfav)
{
	int i = 0;
	my_list *Newnode;

	for (i = 0; gfav->arg_values[i]; i++)
	{
		if (gfav->arg_values[i][0] != '$' || !gfav->arg_values[i][1])
			continue;

		if (!_strcmp(gfav->arg_values[i], "$?"))
		{
			rpl_str(&(gfav->arg_values[i]),
				_strdup(conv_numb(gfav->execution_status, 10, 0)));
			continue;
		}
		if (!_strcmp(gfav->arg_values[i], "$$"))
		{
			rpl_str(&(gfav->arg_values[i]),
				_strdup(conv_numb(getpid(), 10, 0)));
			continue;
		}
		Newnode = node_starts(gfav->environment_list, &gfav->arg_values[i][1], '=');
		if (Newnode)
		{
			rpl_str(&(gfav->arg_values[i]),
				_strdup(_strchr(Newnode->data, '=') + 1));
			continue;
		}
		rpl_str(&gfav->arg_values[i], _strdup(""));

	}
	return (0);
}

/**
 * rpl_str - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int rpl_str(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}
