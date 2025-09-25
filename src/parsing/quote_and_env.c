/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:51:03 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 19:16:47 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote(char *str)
{
	char	quote;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i])
				i++;
			if (!str[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}

char	**ft_cpy_envp(char **envp)
{
	int		nb_line;
	char	**cpy;
	int		i;

	i = 0;
	nb_line = 0;
	while (envp[nb_line])
		nb_line++;
	cpy = malloc(sizeof(char *) * (nb_line + 1));
	if (!cpy)
		return (NULL);
	while (i < nb_line)
	{
		cpy[i] = ft_strdup(envp[i]);
		if (!cpy[i])
		{
			while (--i >= 0)
				free(cpy[i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_token_words(t_token_word *head)
{
	t_token_word	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->word);
		free(head);
		head = tmp;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->type == TOK_WORD && head->word)
			free_token_words(head->word);
		free(head);
		head = tmp;
	}
}