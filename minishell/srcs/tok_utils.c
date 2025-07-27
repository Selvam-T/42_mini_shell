/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 02:30:12 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 01:55:02 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tok_operator(char *s)
{
	if (!ft_strncmp(s, "&&", -1))
		return (OPERATOR_AND);
	else if (!ft_strncmp(s, "||", -1))
		return (OPERATOR_OR);
	else if (!ft_strncmp(s, "|", -1))
		return (OPERATOR_PIPE);
	else if (!ft_strncmp(s, "(", -1))
		return (OPEN_BRACKET);
	else if (!ft_strncmp(s, ")", -1))
		return (CLOSE_BRACKET);
	return (-1);
}

int	is_operator(char *s, int len, int count_redir)
{
	int		one_len;
	int		two_len;

	one_len = 1;
	two_len = 2;
	if (len == -1)
	{
		one_len = len;
		two_len = len;
	}
	if (!ft_strncmp(s, "&&", two_len) || !ft_strncmp(s, "||", two_len)
		|| (!ft_strncmp(s, "<<", two_len) && count_redir)
		|| (!ft_strncmp(s, ">>", two_len) && count_redir))
		return (two_len);
	if (!ft_strncmp(s, "|", one_len) || !ft_strncmp(s, "(", one_len)
		|| !ft_strncmp(s, ")", one_len)
		|| (!ft_strncmp(s, "<", one_len) && count_redir)
		|| (!ft_strncmp(s, ">", one_len) && count_redir))
		return (one_len);
	return (0);
}

char	*token_str(int id)
{
	if (id == 1)
		return ("|");
	if (id == 2)
		return ("&&");
	if (id == 3)
		return ("||");
	if (id == 4)
		return ("(");
	if (id == 5)
		return (")");
	return (NULL);
}

t_input	*find_lastnode(t_input *head)
{
	while (head->right)
		head = head->right;
	return (head);
}

void	add_new_node(t_input **head, t_input *new)
{
	t_input	*current;

	if (*head == NULL)
	{
		*head = new;
		new->right = NULL;
		new->left = NULL;
		return ;
	}
	current = find_lastnode(*head);
	current->right = new;
	new->right = NULL;
	new->left = current;
}
