#include "shell.h"

/*structure for built-In commands */
struct aw_BuiltInCmd {
    char *cmd;
    void (*awfunction)(void);
};

void aw_exitCmd(void);
void aw_envCmd(void);

/*Array of built-In commands */
struct aw_BuiltInCmd aw_builtInCommands[] = {
    {"exit", aw_exitCmd},
    {"env", aw_envCmd},
};

/** 
 * aw_exitCmd - exit function 
*/

void aw_exitCmd(void)
{
        exit(0);
}

/** 
 * aw_envCmd - env function
 */

void aw_envCmd(void)
{
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

void aw_executeCmd(char *command)
{
    int i;
    for (i = 0; i < (int)(sizeof(aw_builtInCommands) / sizeof(aw_builtInCommands[0])); i++)
    {
        if (strcmp(command, aw_builtInCommands[i].cmd) == 0)
        {
            aw_builtInCommands[i].awfunction();
            return;
        }
    }
}