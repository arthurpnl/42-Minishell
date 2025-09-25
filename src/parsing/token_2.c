/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:20:22 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:22:19 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_quote(char *str)
{
    char	*line;
    int		i;
    int		j;

    i = 1;
    j = 0;
    line = malloc(sizeof(char) * (ft_strlen(str) - 1));
    if (!line)
        return (NULL);
    while (str[i + 1])
        line[j++] = str[i++];
    line[j] = '\0';
    return (line);
}

int	operator(char *word)
{
    if (word[0] == '<' && !word[1])
        return (TOK_REDIR_IN);
    else if (word[0] == '>' && !word[1])
        return (TOK_REDIR_OUT);
    else if (word[0] == '|' && !word[1])
        return (TOK_PIPE);
    else if (word[0] == '<' && word[1] == '<')
        return (TOK_HEREDOC);
    else if (word[0] == '>' && word[1] == '>')
        return (TOK_REDIR_APPEND);
    return (-1);
}

int	handle_token_error(char **res, t_token **token)
{
    free_split(res);
    free_tokens(*token);
    return (1);
}