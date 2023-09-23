#include "simpshell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	my_gf gfav[] = {MY_STRUCT_INITIALIZER};

	int fdes = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fdes)
		: "r" (fdes));

	if (argc == 2)
	{
		fdes = open(argv[1], O_RDONLY);
		if (fdes == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				ePuts(argv[0]);
				ePuts(": 0: Can't open ");
				ePuts(argv[1]);
				ePutchar('\n');
				ePutchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		gfav->read_file_descriptor = fdes;
	}
	envList(gfav);
	r_hist(gfav);
	ssh(gfav, argv);
	return (EXIT_SUCCESS);
}
