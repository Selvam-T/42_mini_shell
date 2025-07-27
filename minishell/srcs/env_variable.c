/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:41:14 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:14:07 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env(t_minishell *shell, char *find)
{
	char	**new_env;
	int		index;

	index = get_env_arr_index(shell->env, find);
	if (index >= 0)
	{
		new_env = index_removed_env(shell, index);
		if (new_env == NULL)
			return (1);
		free(shell->env);
		shell->env = new_env;
	}
	return (0);
}

char	*update_env(char **env, char *find, char *value)
{
	char	*update;
	int		i;

	update = NULL;
	i = get_env_arr_index(env, find);
	if (i == -1)
		return (NULL);
	if (find[ft_strlen(find) - 1] == '=')
	{
		update = ft_strjoin(find, value);
		free(env[i]);
		env[i] = update;
	}
	return (env[i]);
}

int	add_env(t_minishell *shell, char *name, char *value)
{
	char	**new_env;
	char	*updated;
	int		i;

	updated = update_env(shell->env, name, value);
	if (updated == NULL)
	{
		new_env = mem_alloc(shell->env, 1);
		if (new_env == NULL)
			return (1);
		if (name[ft_strlen(name) - 1] == '=')
			updated = ft_strjoin(name, value);
		else
			updated = ft_strdup(name);
		i = -1;
		while (shell->env[++i])
			new_env[i] = shell->env[i];
		new_env[i] = updated;
		new_env[++i] = NULL;
		free(shell->env);
		shell->env = new_env;
	}
	return (0);
}

int	add_apn_env(t_minishell *shell, char *name, char *append_str)
{
	char	*old_value;
	char	*new_value;
	int		ret;

	old_value = get_env_value(shell->env, name);
	new_value = ft_strjoin(old_value, append_str);
	free_str(&old_value);
	ret = add_env(shell, name, new_value);
	free_str(&new_value);
	return (ret);
}

int	init_env(t_minishell *shell, char **src)
{
	char		**env;
	int			*exs;
	int			i;

	exs = (int *)ft_calloc(1, sizeof(int));
	env = mem_alloc(src, 0);
	if (env == NULL)
		return (1);
	i = -1;
	while (src[++i])
		env[i] = ft_strdup(src[i]);
	shell->env = env;
	*exs = 0;
	shell->exit_status = exs;
	return (0);
}
