/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:12:31 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:52:04 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recursive_parse_tree(t_input *start, t_input *end, t_input **t, int i)
{
	int		bracket_count;
	t_input	*found;

	found = NULL;
	bracket_count = 0;
	while (!found)
	{
		if (search_op_and_or(start, end, &found))
			break ;
		else if (search_op_pipe(start, end, &found))
			break ;
		else if (enter_brackets(&start, &end))
		{
			search_command(start, end, &found);
			break ;
		}
		bracket_count++;
	}
	if (!found || found == start->left || found == end->right)
		return (0);
	if (set_tree_node_is_command(t, found, bracket_count))
		return (1);
	return (recursive_parse_tree(start, found->left, &(*t)->left, ++i)
		&& recursive_parse_tree(found->right, end, &(*t)->right, ++i));
}

int	parser(t_minishell *shell)
{
	t_input	*tree;
	int		status;

	if (PARSER_DEBUG)
	{
		printf("\n\n[[ENTERED PARSER]]\n\n[PARSER INPUT:"
			"t_minishell *shell]\naccessing LEXER's output");
		print_parse_string(shell->tree);
	}
	tree = NULL;
	status = recursive_parse_tree(shell->tree, \
		find_lastnode(shell->tree), &tree, 0);
	free_input_str(shell->tree);
	shell->tree = NULL;
	shell->tree = tree;
	if (PARSER_DEBUG)
	{
		printf("\n[PARSER OUTPUT: parse_tree] printing parse tree...\n");
		print_parse_tree(shell->tree, 0);
	}
	return (status);
}
