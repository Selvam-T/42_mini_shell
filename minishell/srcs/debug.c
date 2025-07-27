/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:51:29 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:52:28 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_doubleptr(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr || !ptr[i])
		return ;
	while (ptr[i] != NULL)
	{
		printf("ptr[%d]: %s\n", i, ptr[i]);
		i++;
	}
}

void	print_string_content(t_input *head)
{
	t_cmd	*cmd;
	t_oper	*oper;
	int		j;

	if (head->token == 0)
	{
		j = -1;
		cmd = head->content;
		while (cmd->args[++j] != NULL)
			printf("args[%d]: %s\n", j, cmd->args[j]);
		j = -1;
		while (cmd->redirs && cmd->redirs[++j] != NULL)
			printf("redirs[%d]: %s\n", j, cmd->redirs[j]);
	}
	else
	{
		oper = head->content;
		printf("bracket_count: %d\n", oper->bracket_count);
	}
}

void	print_parse_string(t_input *head)
{
	int		i;
	t_oper	*oper;

	i = 0;
	while (head)
	{
		printf("-------------------------------\n");
		printf("NODE %d\n", head->id);
		printf("address: %p\n", head);
		if (head->token == TOK_COMMAND)
			printf("token: %s\n", "TOK_COMMAND\n");
		else
		{
			oper = head->content;
			printf("token: %s\n", oper->op_str);
		}
		print_string_content(head);
		printf("\n");
		head = head->right;
		i++;
	}
	printf("-------------------------------\n");
}

void	print_tree_found_hierarchy(t_input *found)
{
	t_cmd	*cmd;

	if (found->token == 0)
	{
		cmd = found->content;
		printf("node %d: command [ %s ] at %p\n",
			found->id, cmd->args[0], found);
	}
	else
		printf("node %d: operator [ %s ] at %p\n",
			found->id, (char *)found->content, found);
}

int	print_parse_tree(t_input *tree, int i)
{
	t_cmd	*cmd;
	t_oper	*oper;

	if (!tree)
		return (1);
	if (tree->token == TOK_COMMAND)
	{
		cmd = tree->content;
		printf("tree[%d] node %d: command [ %s ] at %p\n",
			i, tree->id, cmd->args[0], tree);
	}
	else
	{
		oper = tree->content;
		printf("tree[%d] node %d: operator [ %s, bracket_count: %d ] at %p\n", \
			i, tree->id, oper->op_str, oper->bracket_count, tree);
	}
	if (tree->token == TOK_COMMAND)
		return (1);
	return (print_parse_tree(tree->left, ++i) \
		&& print_parse_tree(tree->right, ++i));
}
