#include "minishell.h"

void	free_pipes(int **pipes, int count)
{
    int    i;

    i = 0;
    while(i < count)
    {
        if (pipes[i])
            free(pipes[i]);
        i++;
    }
    free(pipes);
}

void	close_all_pipes(int **pipes, int count)
{
    int    i;

    i = 0;
    if (!pipes)
        return ;
    while (i < count - 1)
    {
        if(pipes[i])
        {
            close(pipes[i][0]);
            close(pipes[i][1]);
        }
        i++;
    }
}