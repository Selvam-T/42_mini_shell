/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:08:01 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 12:25:06 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tok_add_operator_node(char **args, t_input **head, int *id)
{
	int		token;
	t_oper	*oper_node;
	t_input	*new;

	oper_node = malloc(sizeof(t_oper));
	if (!oper_node)
		return ;
	token = tok_operator(*args);
	oper_node->op_str = ft_strdup(*args);
	oper_node->bracket_count = 0;
	new = init_input_node(token, oper_node, ++(*id));
	add_new_node(head, new);
}

int	tok_add_command_node(char ***args, t_input **head, int *id)
{
	int		token;
	t_input	*new;
	t_cmd	*cmd_node;

	token = TOK_COMMAND;
	cmd_node = set_cmd_node(args);
	if (!cmd_node)
		return (0);
	new = init_input_node(token, cmd_node, ++(*id));
	add_new_node(head, new);
	return (1);
}

int	tokenizer(char **args, t_minishell *shell)
{
	t_input	*head;
	int		id;

	id = 0;
	head = NULL;
	while (*args)
	{
		if (*args && is_operator(*args, -1, 0))
		{
			tok_add_operator_node(args, &head, &id);
			args++;
		}
		if (*args && !is_operator(*args, -1, 0))
		{
			if (!tok_add_command_node(&args, &head, &id))
			{
				free_input_str(head);
				*shell->exit_status = 2;
				shell->tree = head;
				return (0);
			}
		}
	}
	shell->tree = head;
	return (1);
}
