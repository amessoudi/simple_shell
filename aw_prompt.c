#include "shell.h"
/**
 * main - entry point of the simple shell
 * @argc: number of command line arguments
 * @argv: array of command line arguments
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	char *aw_line = NULL;
	size_t aw_len = 0;
	ssize_t aw_nread;
	char *aw_token;
	char *aw_args[64];
	int aw_i;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDOUT_FILENO, "aw$ ", 4);
		}

		aw_nread = getline(&aw_line, &aw_len, stdin);
		if (aw_nread == -1)
		{
			free(aw_line);
			if (isatty(STDIN_FILENO) == 1)
			{
				write(STDOUT_FILENO, "\n", 1);
			}
			break;
		}

		aw_i = 0;
		aw_token = strtok(aw_line, " \t\r\n\a");
		while (aw_token != NULL)
		{
			aw_args[aw_i++] = aw_token;
			if (aw_i >= 63)
			{
				write(STDOUT_FILENO, "Error: too many arguments\n", 26);
				break;
			}
			aw_token = strtok(NULL, " \t\r\n\a");
		}
		aw_args[aw_i] = NULL;

		if (aw_args[0]) /* If there's at least one token */
		{
			if (access(aw_args[0], F_OK) != -1)
			{
				aw_execute_command(aw_args[0], aw_args);
			}
			else
			{
				write(STDOUT_FILENO, aw_args[0], strlen(aw_args[0]));
				write(STDOUT_FILENO, ": command not found\n", 20);
			}
		}
	}

	exit(EXIT_SUCCESS);
}
