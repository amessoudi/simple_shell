#include "shell.h"
#define NUM_BUILT_IN_CMDS 3
/**
 * aw_execute_command - executes the command
 * @aw_cmd: the command to execute
 * @aw_args: arguments for the command
 *
 * Return: 1 on success, or error code
 */
int aw_execute_command(char *aw_cmd, char **aw_args)
{
	for (int i = 0; i < NUM_BUILT_IN_CMDS; i++)
	{
		if (strcmp(aw_cmd, aw_builtInCommands[i].cmd) == 0) {

			aw_builtInCommands[i].awfunction(aw_args);

		}
	}

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
