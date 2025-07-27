/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 22:41:30 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:56:57 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recursive_check_heredoc(t_input *tree)
{
	int		i;
	char	**redirs;
	t_cmd	*cmd;

	i = -1;
	if (tree->token == TOK_COMMAND)
	{
		cmd = tree->content;
		if (!cmd->redirs || cmd->redirs[0] == NULL)
			return (0);
		redirs = cmd->redirs;
		while (redirs[++i])
		{
			if (redirs[i][0] == '<' && redirs[i][1] == '<')
				return (1);
		}
		return (0);
	}
	return (recursive_check_heredoc(tree->left)
		|| recursive_check_heredoc(tree->right));
}

int	exec_pipe_right(t_minishell *shell, t_input *node, int *fd, int *pipes)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fd[1]);
		fd[1] = pipes[1];
		exit_free_all(shell, recursive_executor(shell, node->right, fd), 0);
	}
	return (pid);
}

int	exec_pipe_left(t_minishell *shell, t_input *node, int *fd, int *pipes)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		close(fd[0]);
		fd[0] = pipes[0];
		exit_free_all(shell, recursive_executor(shell, node->left, fd), 0);
	}
	if (recursive_check_heredoc(node->left))
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
		if (status == 130)
		{
			*shell->exit_status = 130;
			return (-1);
		}
	}
	return (pid);
}

int	close_wait_pipe(int *fds, int *pids, int flag, int status2)
{
	int	status;

	close(fds[0]);
	close(fds[1]);
	if (flag)
	{
		waitpid(pids[0], NULL, 0);
		return (status2);
	}
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], &status, 0);
	status = WEXITSTATUS(status);
	return (status);
}

int	execute_handle_pipe(t_minishell *shell, t_input *node, int *pipes)
{
	int	fds[2];
	int	pids[2];
	int	status;
	int	flag;

	flag = 0;
	if (pipe(fds) == -1)
		return (-1);
	if (recursive_check_heredoc(node->right)
		&& !recursive_check_heredoc(node->left))
	{
		flag = 1;
		pids[1] = exec_pipe_right(shell, node, fds, pipes);
		waitpid(pids[1], &status, 0);
		status = WEXITSTATUS(status);
		*shell->exit_status = status;
		if (status == 130)
			return (status);
	}
	pids[0] = exec_pipe_left(shell, node, fds, pipes);
	if (pids[0] == -1)
		return (130);
	if (!flag)
		pids[1] = exec_pipe_right(shell, node, fds, pipes);
	return (close_wait_pipe(fds, pids, flag, status));
}
