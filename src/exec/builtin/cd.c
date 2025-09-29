/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:24:10 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/26 18:09:43 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*find_target(char **args)
{
	char	*target;
	int		args_count;

	args_count = count_args(args);
	target = get_env(args_count, args);
	if (args_count == 1 && ft_strcmp(args[1], "-") != 0)
		return (target = args[1]);
	if (args_count > 1)
		ft_putstr_fd("cd: too many arguments\n", 2);
	return (target);
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
