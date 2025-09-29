/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:18:41 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/24 20:09:13 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char *var_name, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}

static char	*expand_variable(char *res, const char *word, int *i, char **env)
{
	int		start;
	char	*name;
	char	*value;

	start = ++(*i);
	while (is_valid_var_char(word[*i]))
		(*i)++;
	name = ft_substr(word, start, *i - start);
	if (!name)
		return (NULL);
	//res = ft_strjoin(res, get_env_value(name, env));
	value = get_env_value(name, env);
	if (!value)
    	value = "";
	res = ft_strjoin(res, value);
	free(name);
	return (res);
}

char	*expand_dollar(char *res, const char *word, int *i, t_shell_ctx *ctx)
{
	if (word[*i + 1] == '?')
		return (expand_status(res, ctx->last_status, i));
	if (is_valid_var_char(word[*i + 1]))
		return (expand_variable(res, word, i, ctx->env));
	res = ft_strjoin(res, "$");
	(*i)++;
	return (res);
}

static char	*append_char(char *res, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (ft_strjoin(res, tmp));
}

int	expand_token_word(t_token_word *token, t_shell_ctx *ctx)
{
	int		i;
	char	*res;

	if (!token->expendable)
		return (0);
	res = ft_strdup("");
	if (!res)
		return (1);
	i = 0;
	while (token->word[i])
	{
		if (token->word[i] == '$' && token->word[i + 1])
			res = expand_dollar(res, token->word, &i, ctx);
		else
		{
			res = append_char(res, token->word[i]);
			if (res)
				i++;
		}
		if (!res)
			return (1);
	}
	free(token->word);
	token->word = res;
	return (0);
}