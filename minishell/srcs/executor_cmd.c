/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:09:25 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:38:08 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_emptystr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '"' && str[i] != '\'' && str[i] != ' ')
			return (1);
	}
	return (0);
}

int	handle_empty_args(t_minishell *shell, t_cmd *cmd, int flag, int *i)
{
	if (flag == 0)
	{
		if (!cmd->redirs && !check_emptystr(cmd->args[0]))
		{
			print_errmsg("Command '' not found\n", NULL, NULL);
			return (127);
		}
	}
	if (flag == 1)
	{
		if ((!cmd->args || (count_doubleptr_len(cmd->args) == 1
					&& cmd->args[0][0] == '\0' )) && !cmd->redirs)
			return (EXIT_SUCCESS);
		if ((!cmd->args || !cmd->args[*i]) && cmd->redirs)
			return (*shell->exit_status);
		while (cmd->args && cmd->args[*i] != NULL && !ft_strlen(cmd->args[*i]))
			*i += 1;
	}
	return (-1);
}

int	ft_execute(t_minishell *shell, t_cmd *cmd, int i)
{
	int		pid;
	int		status;
	int		exit_status;

	exit_status = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_execve(shell, cmd, i);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = WTERMSIG(status) + 128;
		if (exit_status == 131)
			print_errmsg("Quit (core dumped)\n", NULL, NULL);
		if (exit_status == 130)
			print_errmsg("\n", NULL, NULL);
	}
	return (exit_status);
}

int	execute_handle_cmd(t_minishell *shell, t_cmd *cmd, int *pipes)
{
	int	i;
	int	exit_status;

	i = 0;
	if (handle_empty_args(shell, cmd, 0, &i) == 127)
		return (127);
	expansions(shell, cmd);
	if (redirections(shell, cmd, pipes) == -1)
		return (*shell->exit_status);
	dup2(pipes[0], STDIN_FILENO);
	dup2(pipes[1], STDOUT_FILENO);
	exit_status = handle_empty_args(shell, cmd, 1, &i);
	if (exit_status != -1)
		return (exit_status);
	if (is_notbuiltin(cmd->args[i]) == -1)
		return (ft_execute(shell, cmd, i));
	return (exec_builtin(shell, cmd->args[i], cmd->args + i + 1));
}
