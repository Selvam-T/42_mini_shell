/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:20:01 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:16:46 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_notbuiltin(char *cmd)
{
	if (ft_is_strequal(cmd, "echo"))
		return (1);
	else if (ft_is_strequal(cmd, "pwd"))
		return (1);
	else if (ft_is_strequal(cmd, "env"))
		return (1);
	else if (ft_is_strequal(cmd, "export"))
		return (1);
	else if (ft_is_strequal(cmd, "unset"))
		return (1);
	else if (ft_is_strequal(cmd, "cd"))
		return (1);
	else if (ft_is_strequal(cmd, "exit"))
		return (1);
	return (-1);
}

int	exec_builtin(t_minishell *ms, char *cmd, char **args)
{
	if (ft_is_strequal(cmd, "echo"))
		return (execute_echo(args));
	else if (ft_is_strequal(cmd, "pwd"))
		return (execute_pwd());
	else if (ft_is_strequal(cmd, "env"))
		return (execute_env(ms, args));
	else if (ft_is_strequal(cmd, "export"))
		return (execute_export(ms, args, 1));
	else if (ft_is_strequal(cmd, "unset"))
		return (execute_unset(ms, args));
	else if (ft_is_strequal(cmd, "cd"))
		return (execute_cd(ms, args, 1));
	else if (ft_is_strequal(cmd, "exit"))
		return (execute_exit(ms, args, 1));
	return (-1);
}

int	ret_exec_builtin(t_minishell *ms, char *cmd, char **args)
{
	if (ft_is_strequal(cmd, "export"))
		execute_export(ms, args, 0);
	else if (ft_is_strequal(cmd, "unset"))
		execute_unset(ms, args);
	else if (ft_is_strequal(cmd, "cd"))
		execute_cd(ms, args, 0);
	else if (ft_is_strequal(cmd, "exit"))
		execute_exit(ms, args, 0);
	return (1);
}
