#include "minishell.h"

void	get_path_env(t_commande *cmd_list, char **env)
{
	int		i;
	char	*path_line;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_line = env[i] + 5;
			cmd_list->path = ft_split_ex(path_line, ':');
			return ;
		}
		i++;
	}
}

char	*create_full_path(t_commande *cmd_list, char **env)
{
	char *cmd_path;
	char *full_path;
	char *cmd;
	int j;

	j = 0;
	cmd = cmd_list->args[0];

	if (!cmd_list->path)
		get_path_env(cmd_list, env);
	if (!cmd_list->path)
		return (NULL);
	while (cmd_list->path && cmd_list->path[j])
	{
		full_path = ft_strjoin(cmd_list->path[j], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		//free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		j++;
	}
	return (NULL);
}