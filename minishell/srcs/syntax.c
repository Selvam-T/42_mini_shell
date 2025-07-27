/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:05:15 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 02:15:54 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check_command(t_input *string)
{
	t_cmd	*cmd;

	while (string)
	{
		if (string->token == TOK_COMMAND)
		{
			cmd = string->content;
			if (!cmd->args[0])
				return (0);
			else
				return (1);
		}
		string = string->right;
	}
	return (0);
}

int	syntax_analyzer(t_input *head)
{
	if (!syntax_check_brackets(head))
		return (-1);
	if (!syntax_check_operators(head))
		return (-1);
	return (1);
}
