#include "simpshell.h"

/**
 * isit_cmd - determines if a file is an executable command
 * @gfav: the gfav struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int isit_cmd(my_gf *gfav, char *path)
{
	struct stat st;

	(void)gfav;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_xter - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_xter(char *pathstr, int start, int stop)
{
	static char buffa[1024];
	int i = 0, j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffa[j++] = pathstr[i];
	buffa[j] = 0;
	return (buffa);
}

/**
 * f_path - finds this cmd in the PATH string
 * @gfav: the gfav struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *f_path(my_gf *gfav, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && statWith(cmd, "./"))
	{
		if (isit_cmd(gfav, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_xter(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (isit_cmd(gfav, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * xfree - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int xfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
