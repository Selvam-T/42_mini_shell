/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:37:21 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/12 02:00:22 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_nonvalue(char *s, int *i, int len)
{
	char	*value;

	if (s == NULL)
		value = NULL;
	else
		value = ft_substr(s, *i, len);
	*i += len;
	return (value);
}

char	*get_keyvalue(t_minishell *shell, char *s, int *i)
{
	char	*key;
	char	*value;
	int		j;

	*i += 1;
	j = 0;
	while (s[*i + j] && (ft_isalnum(s[*i + j]) \
			|| s[*i + j] == '_'))
		j++;
	key = ft_substr(s, *i, j);
	value = get_env_value(shell->env, key);
	free_str(&key);
	*i += j;
	return (value);
}

char	*extract_id_value(t_minishell *shell, char *s, int *i, int *t)
{
	char	*value;

	value = NULL;
	if (s == NULL)
		return (NULL);
	if (s[*i + 1] == '\0')
		value = set_nonvalue(s, i, 1);
	else if (s[*i + 1] == 32 || s[*i + 1] == '$')
	{
		if (s[*i + 1] == '$')
			*t -= 1;
		value = set_nonvalue(s, i, 2);
	}
	else if (s[*i + 1] == '?')
	{
		value = ft_itoa(*(shell->exit_status));
		*i += 2;
	}
	else if (ft_isdigit(s[*i + 1]) || (s[*i + 1] != '_'
			&& !ft_isalpha(s[*i + 1])))
		value = set_nonvalue(NULL, i, 2);
	else
		value = get_keyvalue(shell, s, i);
	return (value);
}
