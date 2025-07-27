/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 23:08:03 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:17:22 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_minishell **shell, char **env, int ac, char **av)
{
	int	exit_status;

	if (ac < 0 || av[0] == NULL)
		return (EXIT_FAILURE);
	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	*shell = (t_minishell *)malloc(sizeof(t_minishell) * 1);
	(*shell)->exit_status = &exit_status;
	return (init_env(*shell, env));
}

void	run_shell(t_minishell *shell)
{
	int		status;
	char	**args;

	while (1)
	{
		status = read_input(shell, &args);
		if (status == -1)
			break ;
		if (status && !run_input(args, shell))
			break ;
	}
}

int	run_input(char **args, t_minishell *shell)
{
	if (lexer(args, shell) == -1)
		return (-1);
	if (parser(shell) == 0)
		return (0);
	executor(shell);
	free_input_tree(&shell->tree);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*shell;

	if (init(&shell, env, ac, av))
		return (EXIT_FAILURE);
	run_shell(shell);
	rl_clear_history();
	exit_free_all(shell, *shell->exit_status, 1);
}
