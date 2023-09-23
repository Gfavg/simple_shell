#include "simpshell.h"

/**
 * ssh - main shell loop
 * @gfav: the parameter & return gfav struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int ssh(my_gf *gfav, char **argv)
{
	ssize_t r = 0;
	int built_dp = 0;

	while (r != -1 && built_dp != -2)
	{
		cl_info(gfav);
		if (interack(gfav))
			_puts("$ ");
		ePutchar(BUFFER_FLUSH);
		r = get_inp(gfav);
		if (r != -1)
		{
			s_info(gfav, argv);
			built_dp = f_builtin(gfav);
			if (built_dp == -1)
				f_cmd(gfav);
		}
		else if (interack(gfav))
			_putchar('\n');
		fr_info(gfav, 0);
	}
	wr_hist(gfav);
	fr_info(gfav, 1);
	if (!interack(gfav) && gfav->execution_status)
		exit(gfav->execution_status);
	if (built_dp == -2)
	{
		if (gfav->error_number == -1)
			exit(gfav->execution_status);
		exit(gfav->error_number);
	}
	return (built_dp);
}

/**
 * f_builtin - finds a builtin command
 * @gfav: the parameter & return gfav struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int f_builtin(my_gf *gfav)
{
	int i, built_in_ret = -1;
	my_cmd builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(gfav->arg_values[0], builtintbl[i].type) == 0)
		{
			gfav->line_counter++;
			built_in_ret = builtintbl[i].function(gfav);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - finds a command in PATH
 * @gfav: the parameter & return gfav struct
 *
 * Return: void
 */
void f_cmd(my_gf *gfav)
{
	char *path = NULL;
	int i, k;

	gfav->path = gfav->arg_values[0];
	if (gfav->linecount_flag == 1)
	{
		gfav->line_counter++;
		gfav->linecount_flag = 0;
	}
	for (i = 0, k = 0; gfav->arguments[i]; i++)
		if (!delim_ch(gfav->arguments[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = f_path(gfav, get_env(gfav, "PATH="), gfav->arg_values[0]);
	if (path)
	{
		gfav->path = path;
		ch_cmd(gfav);
	}
	else
	{
		if ((interack(gfav) || get_env(gfav, "PATH=")
			|| gfav->arg_values[0][0] == '/') && isit_cmd(gfav, gfav->arg_values[0]))
			ch_cmd(gfav);
		else if (*(gfav->arguments) != '\n')
		{
			gfav->execution_status = 127;
			p_error(gfav, "not found\n");
		}
	}
}

/**
 * ch_cmd - forks a an exec thread to run cmd
 * @gfav: the parameter & return gfav struct
 *
 * Return: void
 */
void ch_cmd(my_gf *gfav)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(gfav->path, gfav->arg_values, getEnv(gfav)) == -1)
		{
			fr_info(gfav, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(gfav->execution_status));
		if (WIFEXITED(gfav->execution_status))
		{
			gfav->execution_status = WEXITSTATUS(gfav->execution_status);
			if (gfav->execution_status == 126)
				p_error(gfav, "Permission denied\n");
		}
	}
}
