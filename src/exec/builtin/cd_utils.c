/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:23:09 by arpenel           #+#    #+#             */
/*   Updated: 2025/09/29 18:00:22 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2);
		free(path);
		return (NULL);
	}
	return (path);
}

int	change_dir(char *target)
{
	if (chdir(target) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	free_path(char *new_path, char *old_path)
{
	if (new_path)
		free(new_path);
	if (old_path)
		free(old_path);
}
