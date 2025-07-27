/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:13:22 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:58:21 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_args(t_minishell *shell, char **args, int print)
{
	if (args[1])
	{
		if (print)
			print_errmsg("exit\nminishell: too many arguments\n", NULL, NULL);
		*shell->exit_status = 1;
		return (0);
	}
	return (1);
}

void	check_numeric_arg(t_minishell *shell, char *str, int print)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-'
			&& str[i] != '+')
		{
			if (print)
				print_errmsg("exit\nminishell: exit: ", str,
					": numeric argument required\n");
			exit_free_all(shell, 2, 0);
		}
	}
}

int	execute_exit(t_minishell *shell, char **args, int print)
{
	int	exit_num;

	exit_num = *shell->exit_status;
	if (args[0])
	{
		exit_num = ft_atoi(args[0]);
		check_numeric_arg(shell, args[0], print);
		if (!exit_args(shell, args, print))
			return (1);
	}
	if (print)
		printf("exit\n");
	exit_free_all(shell, exit_num, 0);
	return (0);
}
