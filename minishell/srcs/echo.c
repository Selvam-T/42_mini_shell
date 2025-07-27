/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:37:44 by sthiagar          #+#    #+#             */
/*   Updated: 2024/02/23 12:39:50 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_args(char **args, int *i)
{
	while (args[*i])
	{
		write(1, args[*i], ft_strlen(args[*i]));
		if (!(args[*i + 1] == NULL))
			write(1, " ", 1);
		*i += 1;
	}
	return (0);
}

int	execute_echo(char **args)
{
	int	i;
	int	nl_flag;

	if (args == NULL || args[0] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	nl_flag = 0;
	if (ft_is_strequal(args[0], "-n"))
	{
		nl_flag = 1;
		i = 1;
	}
	display_args(args, &i);
	if (!nl_flag || i == 0)
		write(1, "\n", 1);
	return (0);
}
