/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dupnode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:11:55 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 01:53:05 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*dup_cmd_content(t_cmd *node_cmd)
{
	t_cmd	*ret_cmd;

	ret_cmd = malloc(sizeof(t_cmd));
	if (!ret_cmd)
		return (NULL);
	ret_cmd->args = malloc(sizeof(char *) * \
		(count_doubleptr_len(node_cmd->args) + 1));
	ret_cmd->args[0] = NULL;
	if (!ret_cmd->args)
		return (free_cmd_malloc_fail(NULL, (void **)&ret_cmd));
	ft_argscat(&ret_cmd->args, node_cmd->args);
	if (count_doubleptr_len(node_cmd->redirs))
	{
		ret_cmd->redirs = malloc(sizeof(char *) * \
			(count_doubleptr_len(node_cmd->redirs) + 1));
		ret_cmd->redirs[0] = NULL;
		if (!ret_cmd->redirs)
			return (free_cmd_malloc_fail(&ret_cmd->args, (void **)&ret_cmd));
		ft_argscat(&ret_cmd->redirs, node_cmd->redirs);
	}
	else
		ret_cmd->redirs = NULL;
	return (ret_cmd);
}

t_oper	*dup_oper_content(t_oper *node_oper)
{
	t_oper	*ret_oper;

	ret_oper = malloc(sizeof(t_oper));
	if (!ret_oper)
		return (NULL);
	ret_oper->op_str = ft_strdup(node_oper->op_str);
	ret_oper->bracket_count = node_oper->bracket_count;
	return (ret_oper);
}

int	dup_input_content(t_input **node, t_input **ret)
{
	t_cmd	*ret_cmd;
	t_cmd	*node_cmd;
	t_oper	*node_oper;

	if ((*ret)->token == TOK_COMMAND)
	{
		node_cmd = (*node)->content;
		ret_cmd = dup_cmd_content(node_cmd);
		if (!ret_cmd)
		{
			free_with_ptr((void **)ret);
			return (-1);
		}
		(*ret)->content = ret_cmd;
	}
	else
	{
		node_oper = (*node)->content;
		(*ret)->content = dup_oper_content(node_oper);
	}
	return (1);
}

t_input	*dup_input_node(t_input *node)
{
	t_input	*ret;

	ret = malloc(sizeof(t_input));
	if (!ret)
		return (NULL);
	ret->id = node->id;
	ret->token = node->token;
	dup_input_content(&node, &ret);
	ret->right = NULL;
	ret->left = NULL;
	return (ret);
}

int	set_tree_node_is_command(t_input **tree, t_input *found, int c_brac)
{
	t_oper	*oper_node;

	*tree = dup_input_node(found);
	if ((*tree)->token == TOK_COMMAND)
	{
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		return (1);
	}
	else
	{
		oper_node = (*tree)->content;
		oper_node->bracket_count = c_brac;
	}
	return (0);
}
