/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:42:11 by arthur            #+#    #+#             */
/*   Updated: 2025/09/29 19:00:57 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i - 1);
}

void	print_error(char	**args)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(char **args, t_shell_ctx *ctx)
{
	int	arg_count;

	if (!args || !args[0])
		return (1);
	
	arg_count = count_args(args);
	if (arg_count == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (arg_count == 1)
	{
		printf("exit\n");
		if (is_valid_number(args[1]))
			exit(ft_atoi(args[1]) % 256);
		else
		{
			print_error(args);
			exit(2);
		}
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	return (1);
}
