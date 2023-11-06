#include "shell.h"

/**
 * aw_get_path - retrieves the PATH environment variable
 *
 * Return: pointer to the PATH value, or NULL if not found
 */
char *aw_get_path(void)
{
	int aw_i = 0;

	while (environ[aw_i] != NULL)
	{
		if (strncmp(environ[aw_i], "PATH=", 5) == 0)
		{
			return (environ[aw_i] + 5);
		}
		aw_i++;
	}
	return (NULL);
}

/**
 * aw_check_access - checks if the command can be accessed and executed
 * @aw_token: current PATH token being inspected
 * @aw_cmd: the command to append to the PATH token
 *
 * Return: full path if command is executable, NULL otherwise
 */
char *aw_check_access(char *aw_token, char *aw_cmd)
{
	char *aw_full_path = malloc(1024); /* Adjust size as needed */

	if (aw_full_path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	snprintf(aw_full_path, 1024, "%s/%s", aw_token, aw_cmd);
	if (access(aw_full_path, X_OK) == 0)
	{
		return (aw_full_path);
	}
	free(aw_full_path);
	return (NULL);
}

/**
 * aw_find_command_in_path - searches for a command in the PATH
 * @aw_cmd: the command to find
 *
 * Return: full path of command if found, NULL otherwise
 */
char *aw_find_command_in_path(char *aw_cmd)
{
	char *aw_path, *aw_path_copy, *aw_token, *aw_full_path;
	int aw_length;

	if (strchr(aw_cmd, '/'))
	{
		/* aw_cmd contains a path, no need to search in PATH */
		return (strdup(aw_cmd));
	}

	aw_path = aw_get_path();
	if (aw_path == NULL)
	{
		return (NULL);
	}

	aw_length = strlen(aw_path) + 1;
	aw_path_copy = malloc(aw_length);
	if (aw_path_copy == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	strcpy(aw_path_copy, aw_path);
	aw_token = strtok(aw_path_copy, ":");
	while (aw_token != NULL)
	{
		aw_full_path = aw_check_access(aw_token, aw_cmd);
		if (aw_full_path != NULL)
		{
			free(aw_path_copy);
			return (aw_full_path);
		}
		aw_token = strtok(NULL, ":");
	}
	free(aw_path_copy);
	return (NULL);
}
