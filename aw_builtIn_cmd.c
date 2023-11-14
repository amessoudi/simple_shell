#include "shell.h"

/*structure for built-In commands */


void aw_exitCmd(char **args);
void aw_envCmd(char **args);

/*Array of built-In commands */
struct aw_BuiltInCmd aw_builtInCommands[] = {
	{"exit", aw_exitCmd},
	{"env", aw_envCmd},
	{"cd", aw_cdCmd},
};

/**
 * aw_exitCmd - exit function
*/

void aw_exitCmd(char **args)
{
	(void)args;
	exit(0);
}

/**
 * aw_envCmd - env function
 */

void aw_envCmd(char **args)
{
	(void)args;
	extern char **environ;
	char **awenv;

	for (awenv = environ; *awenv; awenv++)
	{
	   write(STDOUT_FILENO, *awenv, strlen(*awenv));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * aw_executeCmd - execute a built-In command function
 */

void aw_executeCmd(char *command, char **args)
{
	int i;
	for (i = 0; i < (int)(sizeof(aw_builtInCommands) / sizeof(aw_builtInCommands[0])); i++)
	{
		if (strcmp(command, aw_builtInCommands[i].cmd) == 0)
		{
			aw_builtInCommands[i].awfunction(args);
			return;
		}
	}
}

void aw_cdCmd(char **args)
{
	char *homeDir = getenv("HOME");
	char *oldpwd = getenv("OLDPWD");
	char *pwd = getenv("PWD");
	char *targetDir = args[1];


	if (targetDir == NULL) {
		if (homeDir == NULL) {
			perror("cd: HOME not set");
			return;
		}
		targetDir = homeDir;
	} else if (strcmp(targetDir, "-") == 0) {
		if (oldpwd == NULL) {
			perror("cd: OLDPWD not set");
			return;
		}
		targetDir = oldpwd;
		printf("%s\n", targetDir);
	}


	if (chdir(targetDir) != 0) {
		perror("cd");
		return;
	}


	if (pwd != NULL) {
		setenv("OLDPWD", pwd, 1);
	}

	char currentDir[1024];
	if (getcwd(currentDir, sizeof(currentDir)) != NULL) {
		setenv("PWD", currentDir, 1);
	} else {
		perror("getcwd");
	}
}