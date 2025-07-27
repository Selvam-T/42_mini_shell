/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsung <emsung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:05:39 by emma              #+#    #+#             */
/*   Updated: 2024/04/19 14:08:27 by emsung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, char *var_name)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, ft_strlen(var_name)))
		{
			if (env[i][ft_strlen(var_name)] == '\0')
				return (NULL);
			return (env[i] + ft_strlen(var_name) + 1);
		}
	}
	return (NULL);
}

char	*find_pathname(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*ret;

	i = -1;
	ret = NULL;
	paths = ft_split(ft_getenv(env, "PATH"), ':');
	if (!paths && access(cmd, F_OK))
		return (print_ret_null("Unable to find paths list in env."));
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		ret = ft_strdup(cmd);
	while (paths && paths[++i])
	{
		paths[i] = ft_strjoin3(ft_strjoin3(paths[i], "/"), cmd);
		if (!access(paths[i], F_OK))
		{
			if (ret)
				free_with_ptr((void **)&ret);
			ret = ft_strdup(paths[i]);
			break ;
		}
	}
	free_doubleptr(paths);
	return (ret);
}

void	ft_execve(t_minishell *shell, t_cmd *cmd, int i)
{
	char	*pathname;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	pathname = find_pathname(cmd->args[i], shell->env);
	if (!pathname)
	{
		print_errmsg(NULL, cmd->args[i], ": command not found\n");
		exit_free_all(shell, 127, 0);
	}
	execve(pathname, cmd->args + i, shell->env);
	perror_execve(shell, cmd, i, &pathname);
	free_with_ptr((void **)&pathname);
	exit_free_all(shell, 127, 0);
}
