#include "minishell.h"

int	count_args(char **args)
{
	int	i;

	i = 1;
	while (args[i])
		i++;
	return (i - 1);
}

char	*get_env(int args_count, char **args)
{
	char	*target;

	target = NULL;
	if (args_count == 0)
	{
		target = getenv("HOME");
		if (!target)
			printf("cd: HOME not set\n");
	}
	else if (args_count == 1 && ft_strcmp(args[1], "-") == 0)
	{
		target = getenv("OLDPWD");
		if (!target)
			printf("cd: OLDPWD not set\n");
	}
	return (target);
}

static char	*find_target(char	**args)
{
	char	*target;
	int		args_count;

	args_count = count_args(args);
	target = get_env(args_count, args);
	if (args_count == 1 && ft_strcmp(args[1], "-") != 0)
		return (target = args[1]);
	if (args_count > 1)
		printf("cd: too many arguments\n");
	return (target);
}

char	*get_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
		free(path);
		return (NULL);
	}
	return (path);
}

int	change_dir(char *target)
{
	if (chdir(target) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	free_path(char	*new_path, char	*old_path)
{
	if (new_path)
		free(new_path);
	if (old_path)
		free(old_path);
}

int	ft_cd(char **args, t_shell_ctx *ctx)
{
	char	*old_path;
	char	*new_path;
	char	*target;

	target = find_target(args);
	if (!target)
		return (1);

	old_path = get_path();
	if (change_dir(target) != 0)
		return (free(old_path), 1);
	new_path = get_path();
	if (new_path == NULL)
		return (free(old_path), 1);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		printf("%s\n", target);
	add_o_update_env(ctx, "PWD", new_path);
	add_o_update_env(ctx, "OLDPWD", old_path);
	free_path(new_path, old_path);
	return (0);
}
