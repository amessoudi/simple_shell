#include "shell.h"
#define NUM_BUILT_IN_CMDS 3
/*structure for built-In commands */


void aw_exitCmd(char **args);
void aw_envCmd(char **args);


/**
 * struct aw_BuiltInCmd - represent built-in commands and
 * their functions
 *@cmd: the built-in command
 *@awfunction: function pointer to the function for a command
 *@args: argument of the function pointer
*/

struct aw_BuiltInCmd aw_builtInCommands[] =
{
	{"exit", aw_exitCmd},
	{"env", aw_envCmd},
	{"cd", aw_cdCmd},
};

/**
 * aw_exitCmd - exit function
 * @args: arguments 
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
	extern char **environ;
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
	char *homeDir = getenv("HOME");
	char *oldpwd = getenv("OLDPWD");
	char *pwd = getenv("PWD");
	char *targetDir = args[1];
	char currentDir[1024];

	if (targetDir == NULL)
	{
		if (homeDir == NULL)
		{
			fprintf(stderr, "./hsh: 1: cd: HOME not set\n");
			return;
		}
		targetDir = homeDir;
	}
	else if (strcmp(targetDir, "-") == 0)
		{
		if (oldpwd == NULL)
		{
			fprintf(stderr, "./hsh: 1: cd: OLDPWD not set\n");
			return;
		}
		targetDir = oldpwd;
		printf("%s\n", targetDir);
	}


	if (chdir(targetDir) != 0)
	{
		fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", targetDir);
		return;
	}


	if (pwd != NULL)
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
