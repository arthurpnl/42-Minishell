#include "minishell.h"

void	get_path_env(t_commande *cmd_list, char **env)
{
	int	i;
	char	*path_line;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_line = env[i] + 5;
			cmd_list->path = ft_split_ex(path_line, ':');
		}
		i++;
	}
}

char	*create_full_path(t_commande	*cmd_list, int i)
{
	char	*cmd_path;
	char	*full_path;
	char	*cmd;
	int	j;

	j = 0;
	cmd = cmd_list->args[i][0];
	while(cmd_list->path && cmd_list->path[j])
	{
		full_path = ft_strjoin(cmd_path, "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		j++;
	}
	return (NULL);
}