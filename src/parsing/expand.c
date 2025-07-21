#include "minishell.h"

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

void	expand(t_token_word *token, char **env)
{
	int		i;
	int		start;
	char	*res;
	char	*var_name;
	char	*var;
	char	one_char[2];

	i = 0;
	res = ft_strdup("");
	if (token->expendable)
	{
		while (token->word[i])
		{
			if (token->word[i] == '$')
			{
				if (!is_valid_var_char(token->word[i + 1]))
				{
					res = ft_strjoin(res, "$");
					i++;
				}
				else
				{
					i++;
					start = i;
					while (is_valid_var_char(token->word[i]))
						i++;
					var_name = ft_substr(token->word, start, (i - start));
					var = get_env_value(var_name, env);
					free(var_name);
					res = ft_strjoin(res, var);
				}
			}
			else
			{
				one_char[0] = token->word[i];
				one_char[1] = '\0';
				res = ft_strjoin(res, one_char);
				i++;
			}
		}
		free(token->word);
		token->word = res;
	}
}

char *get_env_value(char *var_name, char **env)
{
	int i = 0;
	int len = ft_strlen(var_name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return ("");
}


int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}