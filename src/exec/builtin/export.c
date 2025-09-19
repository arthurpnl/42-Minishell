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

static int	export_without_args(t_shell_ctx *ctx)
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

static int	process_single_arg(char *arg, t_shell_ctx *ctx)
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
		ft_printf("export: '%s': not a valid identifier\n", arg);
		return (1);
	}
}

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

int    parse_export_args(char *args, char **name, char **value)
{
    int    i;

    i = 0;
    if (!args || !args[0])
        return (0);

    while(args[i] && args[i] != '=')
        i++;
    *name = ft_substr(args, 0, i);
    if(!*name)
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

void    print_declare_format(char *env_var)
{
    char    *name;
    char    *value;
    int    i;

    i = 0;
    while(env_var[i] && env_var[i] != '=')
        i++;

    name = ft_substr(env_var, 0, i);

    if (env_var[i] == '=')
    {
        value = ft_substr(env_var, i + 1, ft_strlen(env_var));
        ft_printf("declare -x %s=\"%s\"\n", name, value);
        free(value);
    }
    else
        ft_printf("declare -x %s\n", name);
    free(name);
}


static int is_valid_identifier(const char *name)
{
    int i;

    if (!name || !name[0])
        return 0;
    if (!((name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z') || name[0] == '_'))
        return 0;
    i = 1;
    while (name[i])
    {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '_'))
            return 0;
        i++;
    }
    return 1;
}

int    find_var_index(t_shell_ctx *ctx, char *name, char *value)
{
    size_t name_len;
    int    i;

    name_len = ft_strlen(name);
    i = 0;
    while (ctx->env[i])
    {
        if (ft_strncmp(ctx->env[i], name, name_len) == 0)
        {
            if (ctx->env[i][name_len] == '=' || ctx->env[i][name_len] == '\0')
                return (i);
        }
        i++;
    }
    return (-1);
}

int	add_o_update_env(t_shell_ctx *ctx, char *name, char *value)
{
	int		i;

	i = find_var_index(ctx, name, value);
	if (i == -1)
		return (add_new_env(ctx, name, value));
	else
		return (update_var_env(ctx, i, name, value));
}

int	update_var_env(t_shell_ctx *ctx, int i, char *name, char *value)
{
	char *new_entry;

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


int add_new_env(t_shell_ctx *ctx, char *name, char *value)
{
	char	*new_entry;
	char	**new_env;
	int		count;

	count = 0;
	while (ctx->env[count])
		count++;
	new_env = malloc(sizeof (char *) * (count + 2));
	if(!new_env)
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


char	*build_new_entry(char *name, char *value)
{
	char *temp;
	char *new_entry;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	new_entry = ft_strjoin(temp, value);
	free(temp);
	if (!new_entry)
		return (NULL);
	return (new_entry);
}

char	**env_copy(char **env, char **new_env, int count)
{
	int	i;

	i = 0;
	while(i < count)
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