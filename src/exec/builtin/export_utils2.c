/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:34:05 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/26 15:57:57 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *name)
{
	int		i;
	char	c;

	if (!name || !name[0])
		return (0);
	if (!((name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a'
				&& name[0] <= 'z') || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		c = name[i];
		if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
					&& c <= '9') || c == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*build_new_entry(char *name, char *value)
{
	char	*temp;
	char	*new_entry;

	temp = ft_strjoin_nofree(name, "=");
	if (!temp)
		return (NULL);
	new_entry = ft_strjoin_nofree(temp, value);
	free(temp);
	if (!new_entry)
		return (NULL);
	return (new_entry);
}

void	print_declare_format(char *env_var)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	name = ft_substr(env_var, 0, i);
	if (env_var[i] == '=')
	{
		value = ft_substr(env_var, i + 1, ft_strlen(env_var));
		printf("declare -x %s=\"%s\"\n", name, value);
		free(value);
	}
	else
		printf("declare -x %s\n", name);
	free(name);
}
