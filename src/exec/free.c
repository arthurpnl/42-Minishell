#include "minishell.h"

void	free_pipes(int *pipes, int count)
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