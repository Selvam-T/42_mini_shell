/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsung <emsung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:09:44 by emma              #+#    #+#             */
/*   Updated: 2024/04/19 14:08:45 by emsung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expanded_args(t_minishell *shell, char **args)
{
	char	**expanded;
	char	**ret;
	int		i;

	i = -1;
	ret = NULL;
	while (args[++i])
	{
		expanded = parse_argument(shell, args[i]);
		ret = ft_argsjoin(ret, expanded);
		free_doubleptr(expanded);
		expanded = NULL;
	}
	return (ret);
}

void	expansions(t_minishell *shell, t_cmd *cmd)
{
	char	**args_ret;
	char	**redir_ret;

	args_ret = expanded_args(shell, cmd->args);
	free_doubleptr(cmd->args);
	cmd->args = args_ret;
	if (INPUT_EXPANSION)
	{
		printf("CMD ARGS after parse_argument:");
		print_doubleptr(cmd->args);
	}
	if (!cmd->redirs)
		return ;
	redir_ret = expanded_args(shell, cmd->redirs);
	free_doubleptr(cmd->redirs);
	cmd->redirs = redir_ret;
	if (INPUT_EXPANSION)
	{
		printf("CMD REDIRS after parse_argument:");
		print_doubleptr(cmd->redirs);
	}
	return ;
}
