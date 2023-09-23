#include "simpshell.h"

/**
 * ghist_file - gets the history file
 * @gfav: parameter struct
 *
 * Return: allocated string containg history file
 */

char *ghist_file(my_gf *gfav)
{
	char *buffa, *dir;

	dir = get_env(gfav, "HOME=");
	if (!dir)
		return (NULL);
	buffa = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buffa)
		return (NULL);
	buffa[0] = 0;
	_strcpy(buffa, dir);
	_strcat(buffa, "/");
	_strcat(buffa, HISTORY_FILE);
	return (buffa);
}

/**
 * wr_hist - creates a file, or appends to an existing file
 * @gfav: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wr_hist(my_gf *gfav)
{
	ssize_t fdes;
	char *filename = ghist_file(gfav);
	my_list *node = NULL;

	if (!filename)
		return (-1);

	fdes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdes == -1)
		return (-1);
	for (node = gfav->history_data; node; node = node->next_node)
	{
		Putsfd(node->data, fdes);
		Putsfd("\n", fdes);
	}
	Putfd(BUFFER_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * r_hist - reads history from file
 * @gfav: the parameter struct
 *
 * Return: history_count on success, 0 otherwise
 */
int r_hist(my_gf *gfav)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = ghist_file(gfav);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			b_hist_list(gfav, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		b_hist_list(gfav, buf + last, linecount++);
	free(buf);
	gfav->history_count = linecount;
	while (gfav->history_count-- >= MAX_HISTORY_ENTRIES)
		delnode_n(&(gfav->history_data), 0);
	renum_hist(gfav);
	return (gfav->history_count);
}

/**
b_hist_list * @gfav: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, history_count
 *
 * Return: Always 0
 */
int b_hist_list(my_gf *gfav, char *buf, int linecount)
{
	my_list *node = NULL;

	if (gfav->history_data)
		node = gfav->history_data;
	addNode_end(&node, buf, linecount);

	if (!gfav->history_data)
		gfav->history_data = node;
	return (0);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @gfav: Structure containing potential arguments. Used to maintain
 *
 * Return: the new history_count
 */
int renum_hist(my_gf *gfav)
{
	my_list *node = gfav->history_data;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next_node;
	}
	return (gfav->history_count = i);
}
