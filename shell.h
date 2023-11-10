#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

ssize_t aw_getline(char **lineptr, size_t *n, FILE *stream);
int aw_execute_command(char *aw_cmd, char **aw_args);
char *aw_get_path(void);
char *aw_check_access(char *aw_token, char *aw_cmd);
char *aw_find_command_in_path(char *aw_cmd);
void aw_exitCmd(void);
void aw_envCmd(void);
void aw_executeCmd(char *command);


#endif
