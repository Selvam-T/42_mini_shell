/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:52:49 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/09 16:53:03 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_minishell *ms, char **args)
{
	int	i;

	if (args == NULL || args[0] == NULL)
		return (0);
	i = -1;
	while (args[++i] != NULL)
		delete_env(ms, args[i]);
	return (0);
}
