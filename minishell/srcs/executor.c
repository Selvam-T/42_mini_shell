/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:09:58 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:56:26 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recursive_executor(t_minishell *shell, t_input *tree, int *pipes)
{
	if (EXECUTOR_DEBUG)
	{
		printf("pid in recursive: %d\n", getpid());
		printf("tree head node token and id: %d, %d\n", tree->token, tree->id);
	}
	if (tree->token == TOK_COMMAND)
		return (execute_handle_cmd(shell, tree->content, pipes));
	else if (tree->token == OPERATOR_PIPE)
		return (execute_handle_pipe(shell, tree, pipes));
	else if (tree->token == OPERATOR_AND || tree->token == OPERATOR_OR)
		return (execute_handle_andor(shell, tree, pipes));
	return (-1);
}

void	executor(t_minishell *shell)
{
	int			stdfd[2];
	int			status;
	int			pipes[2];
	t_input		*tree;

	stdfd[0] = dup(STDIN_FILENO);
	stdfd[1] = dup(STDOUT_FILENO);
	pipes[0] = STDIN_FILENO;
	pipes[1] = STDOUT_FILENO;
	dup2(pipes[0], STDIN_FILENO);
	dup2(pipes[1], STDOUT_FILENO);
	tree = shell->tree;
	status = recursive_executor(shell, tree, pipes);
	dup2(stdfd[0], STDIN_FILENO);
	dup2(stdfd[1], STDOUT_FILENO);
	*shell->exit_status = status;
}
