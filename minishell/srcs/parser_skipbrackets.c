/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_skipbrackets.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:55:34 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:54:23 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_inner_brackets(t_input **input, t_input *end, int *flag_bracket)
{
	while (*flag_bracket && (*input)->id <= end->id)
	{
		while ((*input)->token != CLOSE_BRACKET)
		{
			*input = (*input)->right;
			if ((*input)->id == end->id)
				break ;
			if ((*input)->token == OPEN_BRACKET)
				*flag_bracket += 1;
		}
		if ((*input)->id == end->id)
			break ;
		if ((*input)->token == CLOSE_BRACKET)
		{
			*flag_bracket -= 1;
			*input = (*input)->right;
			if ((*input)->id == end->id)
				break ;
		}
	}
}

t_input	*skip_brackets(t_input *node, t_input *end)
{
	t_input	*input;
	int		flag_bracket;

	input = node;
	flag_bracket = 0;
	if (node->token < 4)
		return (node);
	if (input->token == OPEN_BRACKET)
		flag_bracket++;
	skip_inner_brackets(&input, end, &flag_bracket);
	if (!input)
		return (node);
	return (input);
}

int	adjusted_startend(t_input *cur, t_input **startend, int *c, int tok)
{
	if (cur->token == tok)
	{
		if (tok == OPEN_BRACKET)
			*startend = cur->right;
		if (tok == CLOSE_BRACKET)
			*startend = cur;
		*c += 1;
		return (1);
	}
	return (0);
}

int	enter_brackets(t_input **start, t_input **end)
{
	int		count;
	t_input	*current;

	count = 0;
	current = *start;
	if (!current || current->right == *end || current == *end)
		return (1);
	while (current && current->id <= (*end)->id)
	{
		if (adjusted_startend(current, start, &count, OPEN_BRACKET))
			break ;
		current = current->right;
	}
	current = *end;
	while (current && current->id >= (*start)->id)
	{
		if (adjusted_startend(current, end, &count, CLOSE_BRACKET))
			break ;
		current = current->left;
	}
	return (count != 2);
}
