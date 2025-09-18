/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:00:41 by arthur            #+#    #+#             */
/*   Updated: 2025/09/18 18:36:33 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int    ft_export(char **args, t_shell_ctx *ctx)
{
    char    *name;
    char    *value;
    int    i;
    int    status;

    i = 1;
    // mode A : export sans args
    if (!args[1])
    {
        i = 0;
        while(ctx->env[i])
        {
            print_declare_format(ctx->env[i]);
            i++;
        }
        return (0);
    }
    while(args[i])
    {
        parse_export_args(args[i], &name, &value);
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
    if (env_var[i] != '=')
        return;
    name = ft_substr(env_var, 0, i);
    value = ft_substr(env_var, i + 1, ft_strlen(env_var));
    ft_printf("declare -x %s=\"%s\"\n", name, value);
    free(name);
    free(value);
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
