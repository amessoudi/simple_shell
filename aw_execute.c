#include "shell.h"

/**
 * aw_execute_command - executes the command
 * @aw_cmd: the command to execute
 * @aw_args: arguments for the command
 *
 * Return: 1 on success, or error code
 */
int aw_execute_command(char *aw_cmd, char **aw_args)
{
	pid_t aw_pid;
	int aw_status;

	aw_pid = fork();
	if (aw_pid == 0)
	{
		/* Child process */
		if (execve(aw_cmd, aw_args, environ) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
	else if (aw_pid < 0)
	{
		/* Error forking */
		perror("fork");
		return (1);
	}
	else
	{
		/* Parent process */
		do {
			waitpid(aw_pid, &aw_status, WUNTRACED);
		} while (!WIFEXITED(aw_status) && !WIFSIGNALED(aw_status));
	}

	return (WEXITSTATUS(aw_status));
}
