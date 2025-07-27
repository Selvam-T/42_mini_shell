/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_setup_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:11:49 by emma              #+#    #+#             */
/*   Updated: 2024/04/12 02:12:33 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*init_input_node(int token, void *content, int id)
{
	t_input	*new;

	new = malloc(sizeof(t_input));
	if (!new)
		return (NULL);
	new->token = token;
	new->content = content;
	new->id = id;
	return (new);
}

t_cmd	*init_cmd(char **args)
{
	int		count_args;
	int		count_redirs;
	t_cmd	*cmd;

	count_args = 0;
	count_redirs = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (countnum_args_redirs(args, &count_args, &count_redirs) == -1)
	{
		free_with_ptr((void **)&cmd);
		return (NULL);
	}
	cmd->args = (char **)malloc(sizeof(char *) * (count_args + 1));
	if (!cmd->args)
		return (NULL);
	cmd->redirs = (char **)malloc(sizeof(char *) * (count_redirs + 1));
	if (!cmd->redirs)
		return (NULL);
	return (cmd);
}

int	countnum_args_redirs(char **args, int *count_args, int *count_redirs)
{
	while (*args && (!is_operator(*args, -1, 0)))
	{
		if (*args[0] == '>' || *args[0] == '<')
		{
			*count_redirs += 2;
			args++;
			if (!*args || is_operator(*args, -1, 1))
			{
				print_errmsg("minishell: syntax error near"
					"unexpected token 'newline'\n", NULL, NULL);
				return (-1);
			}
		}
		else
			*count_args += 1;
		args++;
	}
	return (1);
}

t_cmd	*set_cmd_node(char ***args)
{
	int		i;
	int		j;
	t_cmd	*ret;

	i = -1;
	j = -1;
	ret = init_cmd(*args);
	if (!ret)
		return (NULL);
	while (**args && (!is_operator(**args, -1, 0)))
	{
		if (**args[0] == '>' || **args[0] == '<')
		{
			ret->redirs[++i] = ft_strdup(**args);
			if (!is_operator(*(++*args), -1, 1))
				ret->redirs[++i] = ft_strdup(**args);
		}
		else
			ret->args[++j] = ft_strdup(**args);
		*args += 1;
	}
	ret->redirs[++i] = NULL;
	ret->args[++j] = NULL;
	return (ret);
}
