/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:08:02 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:28:33 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*free_cmd_malloc_fail(char	***ptr1, void **ptr2)
{
	if (ptr1)
	{
		free_doubleptr(*ptr1);
		*ptr1 = NULL;
		ptr1 = NULL;
	}
	if (ptr2)
		free_with_ptr(ptr2);
	return (NULL);
}

void	exit_free_all(t_minishell *shell, int exit_num, int flag)
{
	free_all(shell, flag);
	exit(exit_num);
}

void	free_all(t_minishell *shell, int flag)
{
	free(shell->exit_status);
	shell->exit_status = NULL;
	free_doubleptr(shell->env);
	if (!flag)
		free_input_tree(&shell->tree);
	shell->env = NULL;
	free(shell);
	shell = NULL;
}
