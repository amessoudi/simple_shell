#include "shell.h"
/**
 *main - check the code
 *@argv: array of command line argument
 *@argc: number of command line argument
 * Return: Always 0.
 */


int main(int argc, char *argv[])
{
	char *aw_line = NULL;
	size_t aw_len = 0;
	ssize_t aw_nread;
	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "aw$ ", 4);
		aw_nread = getline(&aw_line, &aw_len, stdin);

		if (aw_nread == -1)
		{
			free(aw_line);
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		else
		{
			write(STDOUT_FILENO, aw_line, aw_nread);
		}

	}

	exit(EXIT_SUCCESS);
}
