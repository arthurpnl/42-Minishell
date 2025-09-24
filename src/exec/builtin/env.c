#includde "minishell.h"

int    ft_env(char **env)
{
    int    i;

    i = 0;
    if (!env)
        return (1);
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
    return (0);
}