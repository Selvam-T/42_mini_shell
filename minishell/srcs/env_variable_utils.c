/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:26:11 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:10:36 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env_list(char **ptr)
{
	int	i;

	i = 0;
	while (ptr != NULL && ptr[i] != NULL)
	{
		if (ft_strchr(ptr[i], '='))
			printf("%s\n", ptr[i]);
		i++;
	}
}

char	**mem_alloc(char **mem, int resize)
{
	char		**env;
	int			i;

	env = NULL;
	i = -1;
	while (mem[++i])
		continue ;
	i += resize;
	if (i >= 0)
	{
		env = (char **)ft_calloc((i + 1), sizeof(char *));
		if (env == NULL)
			return (NULL);
	}
	return (env);
}

int	get_env_arr_index(char **env, char *find)
{
	int		i;
	int		len;
	char	*sub;

	sub = NULL;
	len = ft_strlen(find);
	if (len && find[len - 1] == '=')
		sub = ft_substr(find, 0, len - 1);
	else
		sub = ft_strdup(find);
	len = ft_strlen(sub);
	i = -1;
	while (env[++i])
	{
		if ((ft_strncmp(env[i], find, len) == 0) && \
			(*(*(env + i) + len) == 0 || \
			*(*(env + i) + len) == '='))
			break ;
	}
	free_str(&sub);
	if (env[i] == NULL)
		return (-1);
	return (i);
}

char	*get_env_value(char **env, char *find)
{
	char	*value;
	int		i;
	int		j;

	if (find == NULL)
		return (NULL);
	value = NULL;
	i = get_env_arr_index(env, find);
	if (i == -1)
		return (NULL);
	j = ft_chrindex(env[i], '=');
	if (j == -1)
		return (NULL);
	value = ft_strdup(*(env + i) + j + 1);
	return (value);
}

char	**index_removed_env(t_minishell *shell, int index)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = mem_alloc(shell->env, -1);
	if (new_env == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i == index)
		{
			free_str(&(shell->env[i]));
			shell->env[i] = NULL;
			i++;
		}
		new_env[j] = shell->env[i];
		if (!shell->env[i])
			break ;
		j++;
		i++;
	}
	new_env[j] = shell->env[i];
	return (new_env);
}
