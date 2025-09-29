/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:31:57 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/26 18:08:19 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_copy(char **env, char **new_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

void	free_old_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	export_without_args(t_shell_ctx *ctx)
{
	int	i;

	i = 0;
	while (ctx->env[i])
	{
		print_declare_format(ctx->env[i]);
		i++;
	}
	return (0);
}

int	process_single_arg(char *arg, t_shell_ctx *ctx)
{
	char	*name;
	char	*value;

	if (parse_export_args(arg, &name, &value))
	{
		if (add_o_update_env(ctx, name, value) != 0)
		{
			free(name);
			if (value)
				free(value);
			return (1);
		}
		free(name);
		if (value)
			free(value);
		return (0);
	}
	else
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg , 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
}

int	parse_export_args(char *args, char **name, char **value)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (0);
	while (args[i] && args[i] != '=')
		i++;
	*name = ft_substr(args, 0, i);
	if (!*name)
		return (0);
	if (!is_valid_identifier(*name))
	{
		free(*name);
		*name = NULL;
		return (0);
	}
	if (args[i] == '=')
		*value = ft_substr(args, i + 1, ft_strlen(args));
	else
		*value = NULL;
	return (1);
}
