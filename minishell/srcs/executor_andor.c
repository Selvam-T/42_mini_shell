/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_andor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:00:56 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:56:40 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_andor_fail(t_input *tree, int status)
{
	t_oper	*current;
	t_oper	*next;

	if ((tree->token == OPERATOR_AND && status != 0)
		|| (tree->token == OPERATOR_OR && status == 0))
	{
		if (tree->right->token == OPERATOR_OR
			|| tree->right->token == OPERATOR_AND)
		{
			current = tree->content;
			next = tree->right->content;
			if (current->bracket_count < next->bracket_count)
				return (1);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}

int	execute_handle_andor(t_minishell *shell, t_input *tree, int *pipes)
{
	int		status1;
	int		status2;

	status2 = -1;
	status1 = recursive_executor(shell, tree->left, pipes);
	if (status1 == 130)
		return (status1);
	status2 = exec_andor_fail(tree, status1);
	if (status2 == 1)
		return (status1);
	if (status2 == 2)
		return (recursive_executor(shell, tree->right->right, pipes));
	return (recursive_executor(shell, tree->right, pipes));
}
