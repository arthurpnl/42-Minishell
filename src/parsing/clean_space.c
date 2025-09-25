/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:41:05 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:12:23 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_single_op(char *str, char *res, int *i, int j)
{
	if (j != 0 && res[j -1] != ' ')
		res[j++] = ' ';
	res[j++] = str[(*i)++];
	if (str[*i] && str[*i] != ' ' && !is_operator(str[*i]))
		res[j++] = ' ';
	return (j);
}

char	*clean_space(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) * 3 + 1));
	if (!res)
		return (NULL);
	i = skip_spaces(str, i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			j = handle_quotes(str, res, &i, j);
		else if (is_double_operator(&str[i]))
			j = handle_double_op(str, res, &i, j);
		else if (is_operator(str[i]))
			j = handle_single_op(str, res, &i, j);
		else if (str[i] == ' ')
			i = skip_spaces2(str, res, i, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

int	is_double_operator(char *str)
{
	return ((str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>'));
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}