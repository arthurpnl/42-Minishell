/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:14:29 by arthur            #+#    #+#             */
/*   Updated: 2025/08/27 17:27:04 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "minishell.h"

int	ft_pwd(void)
{
	char    *pwd_path;

	pwd_path = getcwd(NULL, 0);
	if (!pwd_path)
	{
		perror("getcwd");
		return (1);
	}
	ft_printf("%S\n", pwd_path);
	free(pwd_path);
	return (0);
}*/