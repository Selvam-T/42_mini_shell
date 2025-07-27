/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:17:13 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/03 20:17:29 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extended_display(t_minishell *ms, char **args)
{
	int	i;

	i = 0;
	display_env_list(ms->env);
	while (args[i] != NULL)
	{
		printf("%s\n", args[i]);
		i++;
	}
}

int	execute_env(t_minishell *ms, char **args)
{
	int	i;

	if (args == NULL || args[0] == NULL)
	{
		display_env_list(ms->env);
		return (0);
	}
	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strchr(args[i], '=') == NULL)
		{
			printf("env: ‘%s’: No such file or directory\n", args[i]);
			return (127);
		}
		i++;
	}
	extended_display(ms, args);
	return (0);
}
