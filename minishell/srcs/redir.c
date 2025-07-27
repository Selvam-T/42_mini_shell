/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:07:48 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:57:20 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_open(t_minishell *shell, char *filename, int flag)
{
	if (flag && errno == ENOENT)
		print_errmsg("minishell: ", filename, ": No such file or directory\n");
	if (errno == EACCES)
		print_errmsg("minishell: ", filename, ": Permission denied\n");
	*shell->exit_status = EXIT_FAILURE;
	return (EXIT_FAILURE);
}

int	open_files(t_minishell *shell, char **redirs, int *rdin, int *rdout)
{
	if (redirs[0][0] == '>' && redirs[0][1] == '>')
	{
		*rdout = open(redirs[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*rdout == -1)
			return (perror_open(shell, redirs[0 + 1], 1));
	}
	else if (redirs[0][0] == '>' && redirs[0][0] + 1 != '>')
	{
		*rdout = open(redirs[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*rdout == -1)
			return (perror_open(shell, redirs[1], 0));
	}
	else if (redirs[0][0] == '<' && redirs[0][1] != '<')
	{
		*rdin = open(redirs[1], O_RDONLY);
		if (*rdin == -1)
			return (perror_open(shell, redirs[1], 1));
	}
	return (0);
}

int	redir_iter_heredoc(t_minishell *shell, char **redirs, int *pipes, int *rd)
{
	int	i;

	i = -1;
	while (redirs[++i])
	{
		if (redirs[i][0] == '<' && redirs[i][1] == '<')
		{
			if (!redir_heredoc(shell, redirs[++i], pipes))
				return (-1);
			rd[0] = -1;
		}
	}
	return (0);
}

int	redir_iter_fds(t_minishell *shell, char **redirs, int *rd)
{
	int	status;
	int	i;

	i = -1;
	while (redirs[++i])
	{
		status = open_files(shell, redirs + i, &rd[0], &rd[1]);
		if (status)
			return (-1);
		if (redirs[i][0] == '<' && redirs[i][1] == '<')
			rd[0] = -1;
	}
	return (0);
}

int	redirections(t_minishell *shell, t_cmd *cmd, int *pipes)
{
	char	**redirs;
	int		rd[2];

	rd[0] = -1;
	rd[1] = -1;
	redirs = cmd->redirs;
	if (!redirs || !redirs[0])
		return (0);
	if (redir_iter_heredoc(shell, redirs, pipes, rd) == -1)
		return (-1);
	if (redir_iter_fds(shell, redirs, rd) == -1)
		return (-1);
	if (rd[0] > -1)
		dup2(rd[0], pipes[0]);
	if (rd[1] > -1)
		dup2(rd[1], pipes[1]);
	return (0);
}
