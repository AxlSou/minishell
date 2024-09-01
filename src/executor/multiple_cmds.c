#include "../../includes/minishell.h"

void    multiple_cmds(t_msh *msh)
{
    int     fd[2];
    t_cmd   *cmd;
    int     i;
    char    buf[100000];

    i = 0;
    cmd = msh->cmd;
    if (pipe(fd) == -1)
    {
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    while (cmd)
    {
        printf("Comando: %s\n", cmd->argv[0]);
       
        cmd = cmd->next;
        i++;
    }
}
