#include "simpshell.h"

/**
 * my_exit - exits the shell
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if gfav.arg_values[0] != "exit"
 */
int my_exit(my_gf *gfav)
{
	int exitcheck;

	if (gfav->arg_values[1])  /* If there is an exit arguement */
	{
		exitcheck = e_atoi(gfav->arg_values[1]);
		if (exitcheck == -1)
		{
			gfav->execution_status = 2;
			p_error(gfav, "Illegal number: ");
			ePuts(gfav->arg_values[1]);
			ePutchar('\n');
			return (1);
		}
		gfav->error_number = e_atoi(gfav->arg_values[1]);
		return (-2);
	}
	gfav->error_number = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_cd(my_gf *gfav)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!gfav->arg_values[1])
	{
		dir = get_env(gfav, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = get_env(gfav, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(gfav->arg_values[1], "-") == 0)
	{
		if (!get_env(gfav, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(gfav, "OLDPWD=")), _putchar('\n');
		chdir_ret = 
			chdir((dir = get_env(gfav, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(gfav->arg_values[1]);
	if (chdir_ret == -1)
	{
		p_error(gfav, "can't cd to ");
		ePuts(gfav->arg_values[1]), ePutchar('\n');
	}
	else
	{
		set_env(gfav, "OLDPWD", get_env(gfav, "PWD="));
		set_env(gfav, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @gfav: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_help(my_gf *gfav)
{
	char **arg_array;

	arg_array = gfav->arg_values;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
