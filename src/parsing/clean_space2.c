
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:10:23 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:10:41 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_spaces(char *str, int i)
{
    while (str[i] == ' ')
        i++;
    return (i);
}

int	skip_spaces2(char *str, char *res, int i, int *j)
{
    while (str[i] == ' ')
        i++;
    res[(*j)++] = ' ';
    return (i);
}

int	handle_quotes(char *str, char *res, int *i, int j)
{
    char	quote;

    quote = str[*i];
    res[j++] = str[(*i)++];
    while (str[*i] && str[*i] != quote)
        res[j++] = str[(*i)++];
    if (str[*i] == quote)
        res[j++] = str[(*i)++];
    return (j);
}

int	handle_double_op(char *str, char *res, int *i, int j)
{
    if (j != 0 && res[j -1] != ' ')
        res[j++] = ' ';
    res[j++] = str[*i];
    res[j++] = str[*i];
    (*i) += 2;
    if (str[*i] && str[*i] != ' ' && !is_operator(str[*i]))
        res[j++] = ' ';
    return (j);
}
