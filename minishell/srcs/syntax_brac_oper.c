/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_brac_oper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:06:36 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:49:44 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check_brac_set(t_input **open, t_input **close, int *c, int *s)
{
	if (((*open)->id > 1 && ((*open)->left->token == TOK_COMMAND
				|| (*open)->left->token == CLOSE_BRACKET)))
		return (print_errmsg("minishell: syntax error near"
				" unexpected token ')'\n", NULL, NULL));
	c++;
	s++;
	(*close) = (*close)->right;
	while ((*close) && (*close)->token != CLOSE_BRACKET)
		(*close) = (*close)->right;
	if (!(*close) || ((*close)->left && (*close)->left->token == OPEN_BRACKET)
		|| ((*close)->right && (*close)->right->token == TOK_COMMAND))
		return (print_errmsg("minishell: syntax error near"
				" unexpected token '('\n", NULL, NULL));
	s--;
	return (1);
}

int	syntax_check_brackets(t_input *string)
{
	int		set;
	int		count;
	t_input	*open;
	t_input	*close;

	count = 1;
	set = 0;
	close = string;
	open = string;
	while (open)
	{
		if (open->token == OPEN_BRACKET)
		{
			if (!syntax_check_brac_set(&open, &close, &count, &set))
				return (0);
		}
		else if ((open->id > close->id || open->id == 1)
			&& open->token == CLOSE_BRACKET && set == 0)
			return (print_errmsg("minishell: syntax error near"
					" unexpected token ')'\n", NULL, NULL));
		open = open->right;
	}
	return (count);
}

int	syntax_check_oper_left(t_input *head)
{
	t_input	*neighbour;
	t_oper	*oper;

	neighbour = head->left;
	while (neighbour && neighbour->token == CLOSE_BRACKET)
		neighbour = neighbour->left;
	if ((!neighbour || neighbour->token != TOK_COMMAND)
		&& head->token != -1)
	{
		oper = head->content;
		return (print_errmsg("minishell: syntax error near"
				" unexpected token '", (char *)oper->op_str, "'\n"));
	}
	return (1);
}

int	syntax_check_oper_right(t_input *head)
{
	t_input	*neighbour;
	t_oper	*oper;

	neighbour = head->right;
	while (neighbour && (neighbour->token == OPEN_BRACKET
			|| neighbour->token == -1))
		neighbour = neighbour->right;
	if (!neighbour || neighbour->token != TOK_COMMAND)
	{
		oper = head->right->content;
		if (!head->right)
			print_errmsg("minishell: syntax error near unexpected"
				" token '", (char *)oper->op_str, "'\n");
		else
		{
			print_errmsg("minishell: syntax error near unexpected"
				" token '", (char *)oper->op_str, "'\n");
		}
		return (0);
	}
	return (1);
}

int	syntax_check_operators(t_input *string)
{
	t_input	*head;

	head = string;
	while (head)
	{
		if (head->token != TOK_COMMAND && head->token != OPEN_BRACKET
			&& head->token != CLOSE_BRACKET)
		{
			if (!syntax_check_oper_left(head))
				return (0);
			if (!syntax_check_oper_right(head))
				return (0);
		}
		head = head->right;
		if (head && (head->token == OPEN_BRACKET
				|| head->token == CLOSE_BRACKET))
			head = head->right;
	}
	return (1);
}
