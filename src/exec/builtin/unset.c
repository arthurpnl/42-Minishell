/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 16:30:54 by arthur            #+#    #+#             */
/*   Updated: 2025/09/15 17:38:14 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_unset(char **args, t_shell_ctx *ctx)
{
    int    i;

    i = 1;
    if (!args[i])
        return (1);
    while (args[i])
    {
        int    j;

        j = 0;
        while (ctx->env[j])
        {
            if (ft_strncmp(ctx->env[j], args[i], ft_strlen(args[i])) == 0 &&
                ctx->env[j][ft_strlen(args[i])] == '=')
            {
                free(ctx->env[j]);
                move_var(j, ctx->env);
            }
            else
                j++;
        }
        i++;
    }
    return (0);
}

void    move_var(int i, char **env)
{
    int    j;

    j = i;
    while(env[j])
    {
        env[j] = env[j + 1];
        j++;
    }
    env[j] = NULL;
}