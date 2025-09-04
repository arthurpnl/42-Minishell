/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:42:11 by arthur            #+#    #+#             */
/*   Updated: 2025/09/04 16:03:03 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int    is_valid_number(char *str)
{
    int    i;

    i = 0;
    if (!str || !str[0])
        return (0);
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int    count_args(char **args)
{
    int    i;

    i = 0;
    if (!args)
        return (0);
    while (args[i])
        i++;
    return (i);
}
int    ft_exit(char **args)
{
    int    arg_count;
    int    exit_code;
    if (!args || !args[0])
        return (1);

    arg_count = count_args(args);
    if (arg_count == 1);

}