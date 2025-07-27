/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:53:04 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:57:30 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler_eof_heredoc(int sig)
{
	if (sig != EOF)
		return ;
	print_errmsg("minishell: warning: here-document"
		"delimited by end-of-file instead of specified limiter",
		NULL, NULL);
}

void	sighandler_sigint_rl(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	update_exitstatus(130);
}

void	sighandler_sigint_processes(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	update_exitstatus(int num)
{
	*storage_exitstatus() = num;
}

int	*storage_exitstatus(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}
