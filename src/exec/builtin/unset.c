/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:30:54 by arthur            #+#    #+#             */
/*   Updated: 2025/09/17 16:31:03 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int remove_env_at(t_shell_ctx *ctx, int idx)
{
    int j;

    if (!ctx || !ctx->env || !ctx->env[idx])
        return 0;
    free(ctx->env[idx]);
    j = idx;
    while (ctx->env[j + 1])
    {
        ctx->env[j] = ctx->env[j + 1];
        j++;
    }
    ctx->env[j] = NULL;
    return 1;
}

static int unset_one_arg(t_shell_ctx *ctx, const char *name)
{
    size_t len;
    int j;
    len = ft_strlen(name);
    j = 0;

    while (ctx && ctx->env && ctx->env[j])
    {
        if (ft_strncmp(ctx->env[j], name, len) == 0 && ctx->env[j][len] == '=')
            return remove_env_at(ctx, j);
        j++;
    }
    return 0;
}

int ft_unset(char **args, t_shell_ctx *ctx)
{
    int i;
    int status;

    i = 1;
    status = 0;

    if (!args || !args[1])
        return 0;

    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            ft_putstr_fd("minishell: unset: '", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            status = 1;
        }
        else
            unset_one_arg(ctx, args[i]);
        i++;
    }
    return status;
}