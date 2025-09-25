/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:00:41 by arthur            #+#    #+#             */
/*   Updated: 2025/09/19 18:16:22 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, t_shell_ctx *ctx)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
		return (export_without_args(ctx));
	i = 1;
	while (args[i])
	{
		if (process_single_arg(args[i], ctx) != 0)
			status = 1;
		i++;
	}
	return (status);
}

int	add_o_update_env(t_shell_ctx *ctx, char *name, char *value)
{
	int	i;

	i = find_var_index(ctx, name, value);
	if (i == -1)
		return (add_new_env(ctx, name, value));
	else
		return (update_var_env(ctx, i, name, value));
}

int	update_var_env(t_shell_ctx *ctx, int i, char *name, char *value)
{
	char	*new_entry;

	free(ctx->env[i]);
	if (!value)
	{
		new_entry = ft_strdup(name);
		if (!new_entry)
			return (1);
		ctx->env[i] = new_entry;
		return (0);
	}
	new_entry = build_new_entry(name, value);
	if (!new_entry)
		return (1);
	ctx->env[i] = new_entry;
	return (0);
}

int	add_new_env(t_shell_ctx *ctx, char *name, char *value)
{
	char	*new_entry;
	char	**new_env;
	int		count;

	count = 0;
	while (ctx->env[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	new_env = env_copy(ctx->env, new_env, count);
	if (!value)
		new_entry = ft_strdup(name);
	else
		new_entry = build_new_entry(name, value);
	if (!new_entry)
	{
		free_old_env(new_env);
		return (1);
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	free_old_env(ctx->env);
	ctx->env = new_env;
	return (0);
}

int	find_var_index(t_shell_ctx *ctx, char *name, char *value)
{
	size_t	name_len;
	int		i;

	name_len = ft_strlen(name);
	i = 0;
	while (ctx->env[i])
	{
		if (ft_strncmp(ctx->env[i], name, name_len) == 0)
		{
			if(ctx->env[i][name_len] == '=' || ctx->env[i][name_len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}