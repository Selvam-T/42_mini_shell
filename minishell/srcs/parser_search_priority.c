/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search_priority.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:55:13 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:58:58 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_op_and_or(t_input *start, t_input *end, t_input **find)
{
	if (PARSER_DEBUG)
		printf("searching ANDOR for hierarchy."
			"(start: %p, %d, end: %p, %d)\n", start, start->id, end, end->id);
	while (start && start->id < end->id)
	{
		start = skip_brackets(start, end);
		if (start->token == OPERATOR_OR || start->token == OPERATOR_AND)
		{
			*find = start;
			return (1);
		}
		start = start->right;
	}
	return (0);
}

int	search_op_pipe(t_input *start, t_input *end, t_input **find)
{
	if (PARSER_DEBUG)
		printf("searching pipe for hierarchy. "
			"(start: %p, %d, end: %p, %d)\n", start, start->id, end, end->id);
	if (start == end)
		return (0);
	while (start && start->id <= end->id)
	{
		start = skip_brackets(start, end);
		if (start->token == OPERATOR_PIPE)
		{
			*find = start;
			return (1);
		}
		start = start->right;
	}
	return (0);
}

int	search_command(t_input *start, t_input *end, t_input **find)
{
	int		flag;

	flag = 0;
	if (PARSER_DEBUG)
		printf("searching command for hierarchy. "
			"(start: %p, %d, end: %p, %d)\n", start, start->id, end, end->id);
	while (start)
	{
		start = skip_brackets(start, end);
		if (start->token == TOK_COMMAND)
		{
			*find = start;
			return (1);
		}
		start = start->right;
		if (flag == 1)
			break ;
		if (start == end)
			flag = 1;
	}
	return (0);
}
