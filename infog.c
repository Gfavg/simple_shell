#include "simpshell.h"

/**
 * cl_info - initializes my_gf struct
 * @gfav: struct address
 */
void cl_info(my_gf *gfav)
{
	gfav->arguments = NULL;
	gfav->arg_values = NULL;
	gfav->path = NULL;
	gfav->argument_count = 0;
}

/**
 * s_info - initializes my_gf struct
 * @gfav: struct address
 * @av: argument vector
 */
void s_info(my_gf *gfav, char **av)
{
	int i = 0;

	gfav->filename = av[0];
	if (gfav->arguments)
	{
		gfav->arg_values = strtokk(gfav->arguments, " \t");
		if (!gfav->arg_values)
		{

			gfav->arg_values = malloc(sizeof(char *) * 2);
			if (gfav->arg_values)
			{
				gfav->arg_values[0] = _strdup(gfav->arguments);
				gfav->arg_values[1] = NULL;
			}
		}
		for (i = 0; gfav->arg_values && gfav->arg_values[i]; i++)
			;
		gfav->argument_count = i;

		rpl_alias(gfav);
		rpl_var(gfav);
	}
}

/**
 * fr_info - frees my_gf struct fields
 * @gfav: struct address
 * @all: true if freeing all fields
 */
void fr_info(my_gf *gfav, int all)
{
	freee(gfav->arg_values);
	gfav->arg_values = NULL;
	gfav->path = NULL;
	if (all)
	{
		if (!gfav->command_buffer)
			free(gfav->arguments);
		if (gfav->environment_list)
			frList(&(gfav->environment_list));
		if (gfav->history_data)
			frList(&(gfav->history_data));
		if (gfav->alias_data)
			frList(&(gfav->alias_data));
		freee(gfav->custom_environment);
			gfav->custom_environment = NULL;
		xfree((void **)gfav->command_buffer);
		if (gfav->read_file_descriptor > 2)
			close(gfav->read_file_descriptor);
		_putchar(BUFFER_FLUSH);
	}
}
