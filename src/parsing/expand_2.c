/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:57:40 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 20:00:43 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

char	*expand_status(char *res, int status, int *i)
{
    char	buf[12];

    sprintf(buf, "%d", status);
    *i += 2;
    return (ft_strjoin(res, buf));
}