/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:16:19 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:57:13 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_eof_heredoc_msg(void)
{
	ft_putstr_fd("minishell: warning: here-document "
		"delimited by end-of-file instead of specified limiter\n",
		STDERR_FILENO);
}

char	*read_until_limiter(char *limiter)
{
	char	*buff;
	char	*buff_str;

	signal(SIGINT, sighandler_sigint_processes);
	buff_str = ft_calloc(1, 1);
	buff = readline("> ");
	while (buff)
	{
		if (!ft_strncmp(buff, limiter, -1))
			break ;
		buff = ft_strjoin3(buff, "\n");
		buff_str = ft_strjoin3(buff_str, buff);
		if (!*buff_str)
		{
			free_with_ptr((void **)buff);
			free_with_ptr((void **)buff_str);
			return (NULL);
		}
		free(buff);
		buff = readline("> ");
	}
	if (!buff)
		print_eof_heredoc_msg();
	free_with_ptr((void **)&buff);
	return (buff_str);
}

void	write_buffstr_to_fd(t_minishell *shell, char **buff_str, int *fds)
{
	write(fds[1], *buff_str, ft_strlen(*buff_str));
	close(fds[0]);
	free_with_ptr((void **)buff_str);
	exit_free_all(shell, EXIT_SUCCESS, 0);
}

int	redir_heredoc(t_minishell *shell, char *limiter, int *pipes)
{
	int		fds[2];
	int		pid;
	int		status;
	char	*buff_str;

	if (pipe(fds) == -1)
		return (0);
	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		buff_str = read_until_limiter(limiter);
		if (!buff_str)
			return (0);
		write_buffstr_to_fd(shell, &buff_str, fds);
	}
	close(fds[1]);
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status);
	*shell->exit_status = status;
	if (status == 130)
		return (0);
	pipes[0] = fds[0];
	return (1);
}
