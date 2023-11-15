#include "shell.h"
#define NUM_BUILT_IN_CMDS 3
/*structure for built-In commands */


void aw_exitCmd(char **args);
void aw_envCmd(char **args);



struct aw_BuiltInCmd aw_builtInCommands[] = {
	{"exit", aw_exitCmd},
	{"env", aw_envCmd},
	{"cd", aw_cdCmd},
};

/**
 * aw_exitCmd - exit function
 *@args: arguments
*/

void aw_exitCmd(char **args)
{
	(void)args;
	exit(0);
}

/**
 * aw_envCmd - env function
 * @args: arguments
 */

void aw_envCmd(char **args)
{
	char **awenv;

	(void)args;
	for (awenv = environ; *awenv; awenv++)
	{
		write(STDOUT_FILENO, *awenv, strlen(*awenv));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * aw_executeCmd - execute a built-In command function
 * @command: a command
 * @args: arguments
 */

void aw_executeCmd(char *command, char **args)
{
	int i;

	for (i = 0; i < NUM_BUILT_IN_CMDS; i++)
	{
		if (strcmp(command, aw_builtInCommands[i].cmd) == 0)
		{
			aw_builtInCommands[i].awfunction(args);
			return;
		}
	}
}
/**
 * aw_cdCmd - cd function
 * @args: arguments
*/
void aw_cdCmd(char **args)
{
	char *homeDir, *oldpwd, *pwd, *targetDir;
	char currentDir[1024];

	homeDir = getenv("HOME");
	oldpwd = getenv("OLDPWD");
	pwd = getenv("PWD");
	targetDir = args[1];

	if (targetDir == NULL)
	{
		targetDir = homeDir ? homeDir : pwd; /* Use PWD if HOME is not set */
	}
	else if (strcmp(targetDir, "-") == 0)
	{
		targetDir = oldpwd ? oldpwd : pwd; /* Use PWD if OLDPWD is not set */
		if (targetDir)
		{
			printf("%s\n", targetDir);
		}
	}

	if (targetDir && chdir(targetDir) != 0)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", targetDir);
		return;
	}

	if (pwd)
	{
		setenv("OLDPWD", pwd, 1);
	}

	if (getcwd(currentDir, sizeof(currentDir)) != NULL)
	{
		setenv("PWD", currentDir, 1);
	}
	else
	{
		perror("getcwd");
	}
}
