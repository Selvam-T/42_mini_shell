/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_perror.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsung <emsung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:07:06 by emsung            #+#    #+#             */
/*   Updated: 2024/04/19 14:08:07 by emsung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_shellscript(char *cmd, char **pathname)
{
	int		len;
	int		start;

	len = ft_strlen(cmd);
	if (cmd[len - 3] == '.' && cmd[len - 2] == 's'
		&& cmd[len - 1] == 'h')
	{
		start = 2;
		if (cmd[0] != '.')
			start = 0;
		print_errmsg("minishell: required /bin/bash before ",
			cmd + start, "\n");
	}
	free_with_ptr((void **)pathname);
}

void	perror_eacces(t_minishell *shell, t_cmd *cmd, int i, char **pathname)
{
	int		len;
	char	*err_msg;

	len = ft_strlen(cmd->args[i]);
	err_msg = ft_strjoin3(ft_strjoin(": ", strerror(errno)), "\n");
	if (cmd->args && cmd->args[i] && cmd->args[i][0]
		&& cmd->args[i][0] != '.' && cmd->args[i][1]
		&& cmd->args[i][1] != '/' && cmd->args[i][len - 1]
		&& cmd->args[i][len - 1] == 'h' && cmd->args[i][len - 2]
		&& cmd->args[i][len - 2] == 's')
		print_errmsg("minishell: ", *pathname, err_msg);
	else
		print_errmsg("minishell: ", cmd->args[i], err_msg);
	free_with_ptr((void **)&err_msg);
	free_with_ptr((void **)pathname);
	exit_free_all(shell, 126, 0);
}

void	perror_execve(t_minishell *shell, t_cmd *cmd, int i, char **pathname)
{
	char	*err_msg;

	if (errno == ENOENT)
	{
		err_msg = ft_strjoin3(ft_strjoin(": ", strerror(errno)), "\n");
		print_errmsg("minishell: ", cmd->args[i], err_msg);
		free_with_ptr((void **)&err_msg);
	}
	else if (errno == EACCES)
		perror_eacces(shell, cmd, i, pathname);
	else if (errno == ENOEXEC)
		perror_shellscript(cmd->args[i], pathname);
}
