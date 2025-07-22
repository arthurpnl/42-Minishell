#include "minishell.h"

char	**get_path(char **envp)
{
	int	i;
	char *path_line;
	char **path_array;

	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5)
		{
			path_line = envp[i] + 5;
			path_array = ft_split(path_line, ':');
			return (path_array);
		}
		i++;
	}
	return (NULL);
}