#include "simpshell.h"

/**
 * inp_buf - buffers chained commands
 * @gfav: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t inp_buf(my_gf *gfav, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_hand);
#if SYS_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_lin(gfav, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			gfav->linecount_flag = 1;
			rm_comments(*buf);
			b_hist_list(gfav, *buf, gfav->history_count++);
			{
				*len = r;
				gfav->command_buffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_inp - gets a line minus the newline
 * @gfav: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_inp(my_gf *gfav)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(gfav->arguments), *p;

	_putchar(BUFFER_FLUSH);
	r = inp_buf(gfav, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	
	{
		j = i; 
		p = buf + i; 

		ch_chain(gfav, buf, &j, i, len);
		while (j < len) 
		{
			if (isit_chain(gfav, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len) 
		{
			i = len = 0; 
			gfav->command_buffer_type = COMMAND_NORMAL;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_lin() */
	return (r); /* return length of buffer from get_lin() */
}

/**
 * read_buf - reads a buffer
 * @gfav: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(my_gf *gfav, char *buffa, size_t *k)
{
	ssize_t r = 0;

	if (*k)
		return (0);
	r = read(gfav->read_file_descriptor, buffa, INPUT_BUFFER_SIZE);
	if (r >= 0)
		*k = r;
	return (r);
}

/**
 * get_lin - gets the next line of input from STDIN
 * @gfav: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_lin(my_gf *gfav, char **ptr, size_t *length)
{
	static char buf[INPUT_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(gfav, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_hand - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_hand(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
