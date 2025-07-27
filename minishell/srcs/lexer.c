/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:07:33 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:06:44 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char **args, t_minishell *shell)
{
	int	status;

	if (LEXER_DEBUG)
	{
		printf("\n\n[[ENTERED LEXER]]\n\n[LEXER INPUT:"
			" char **args, t_minishell *shell]\n");
		printf("char **args:\n");
		print_doubleptr(args);
	}
	status = tokenizer(args, shell);
	free_doubleptr(args);
	if (!status)
		return (-1);
	if (LEXER_DEBUG)
	{
		printf("\n[LEXER OUTPUT] printing parse string...\n");
		print_parse_string(shell->tree);
	}
	status = syntax_analyzer(shell->tree);
	if (status == -1)
	{
		*shell->exit_status = 2;
		free_input_str(shell->tree);
	}
	return (status);
}
