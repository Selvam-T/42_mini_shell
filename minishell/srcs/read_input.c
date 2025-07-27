/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:09:47 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 02:02:24 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_input(t_minishell *shell, char ***ptr)
{
	char	*input;
	char	**args;
	int		status;

	status = readline_with_signals(shell, &input);
	if (status == -1)
		return (status);
	if (status)
	{
		add_history(input);
		args = NULL;
		args = format_input(shell, &input);
		*ptr = args;
		if (!args)
			status = 0;
	}
	free_with_ptr((void **)&input);
	return (status);
}

int	readline_with_signals(t_minishell *shell, char **input)
{
	update_exitstatus(*shell->exit_status);
	signal(SIGINT, sighandler_sigint_rl);
	*input = readline("minishell>>$ ");
	signal(SIGINT, SIG_IGN);
	*shell->exit_status = *storage_exitstatus();
	if (!*input)
	{
		printf("exit\n");
		*shell->exit_status = 0;
		return (-1);
	}
	if (*input[0] == '\0')
		return (0);
	return (1);
}

char	**format_input(t_minishell *shell, char **in)
{
	char	**args;
	char	*input;

	input = clean_up_quotes(*in);
	if (!input)
	{
		print_errmsg("minishell: syntax error unclosed quotes\n", NULL, NULL);
		*shell->exit_status = 2;
		return (NULL);
	}
	if (INPUT_EXPANSION)
		printf("return of cleanupquotes: %s\n", input);
	args = rfmt_input(input);
	if (*args == NULL)
		return (NULL);
	if (INPUT_EXPANSION)
	{
		printf("return of rfmt_input: \n");
		print_doubleptr(args);
	}
	free_with_ptr((void **)in);
	*in = input;
	return (args);
}
