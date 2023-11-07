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
	char *aw_full_path;
	int aw_i;
	int aw_last_status = 0;

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
		
	if (aw_args[0]) 
		{
        
            if (strcmp(aw_args[0], "exit") == 0)
			{
				 free(aw_line);
                exit(aw_last_status);
            }
			else
			{

		if (aw_args[0])
			{
			aw_full_path = aw_find_command_in_path(aw_args[0]);
			if (aw_full_path != NULL)
			{
					char error_message[50];
        snprintf(error_message, sizeof(error_message), "%s: %d: %s: not found\n", argv[0], 1, aw_args[0]);
        write(STDERR_FILENO, error_message, strlen(error_message));
        aw_last_status = 127;
         free(aw_full_path);
			}
			else
			{
				char error_message[50];
				snprintf(error_message, sizeof(error_message), "%s: %d: %s: not found\n", argv[0], 1, aw_args[0]);
				write(STDERR_FILENO, error_message, strlen(error_message));
				aw_last_status = 127;
			}
			}
			}
		}
		free(aw_line);
		aw_line = NULL;
		aw_len = 0;
	}

	exit(aw_last_status);
}
