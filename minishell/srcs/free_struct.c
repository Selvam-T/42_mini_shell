/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 00:08:32 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:05:16 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct_oper(t_oper **ptr)
{
	t_oper	*oper;

	oper = *ptr;
	if (!oper)
		return ;
	free(oper->op_str);
	oper->op_str = NULL;
	free(oper);
	oper = NULL;
}

void	free_struct_cmd(t_cmd **ptr)
{
	t_cmd	*node;

	node = *ptr;
	if (LEAKS_DEBUG)
	{
		printf("freeing in struct\n");
		printf("node->args pointer %p\n", node->args);
	}
	if (!node)
		return ;
	free_doubleptr(node->args);
	free_doubleptr(node->redirs);
	node->args = NULL;
	node->redirs = NULL;
	free(node);
	if (LEAKS_DEBUG)
		printf("freed\n");
}

void	free_input_str(t_input *str)
{
	t_input	*cur;
	t_input	*tmp;

	cur = str;
	if (!str)
		return ;
	while (cur)
	{
		tmp = cur;
		cur = cur->right;
		if (tmp->token == TOK_COMMAND)
			free_struct_cmd((t_cmd **)&tmp->content);
		else
			free_struct_oper((t_oper **)&tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_input_tree(t_input **input)
{
	t_input	*tree;

	if (!input || !*input)
		return ;
	tree = *input;
	if (LEAKS_DEBUG)
	{
		printf("freeing node: %d\n", tree->id);
		printf("token: %d\n", tree->token);
		printf("tree ptr: %p\n", tree);
	}
	if (tree->token == TOK_COMMAND)
	{
		if (LEAKS_DEBUG)
			printf("freeing cmd struct\n");
		free_struct_cmd((t_cmd **)&tree->content);
	}
	else
		free_struct_oper((t_oper **)&tree->content);
	tree->content = NULL;
	free_input_tree(&tree->left);
	free_input_tree(&tree->right);
	free(tree);
	tree = NULL;
	input = NULL;
}
