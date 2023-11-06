#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

int aw_execute_command(char *aw_cmd, char **aw_args);
static char *aw_get_path(void);
static char *aw_check_access(char *aw_token, char *aw_cmd);
char *aw_find_command_in_path(char *aw_cmd);



#endif
