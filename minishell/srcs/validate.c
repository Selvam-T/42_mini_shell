/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:45:46 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/12 02:00:09 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_id_chr(char c, int index)
{
	if ((index == 0) && \
		(ft_isdigit(c) || (c != '_' && !ft_isalpha(c))))
		return (0);
	else if ((index > 0) && (!ft_isalnum(c) && c != '_'))
		return (0);
	return (1);
}

int	is_valid_key(char *key)
{
	int	i;
	int	len;

	if (key == NULL)
		return (-1);
	len = ft_strlen(key);
	if (len > 1 && key[len - 1] == '=')
		len = len - 1;
	if (ft_isdigit(key[0]) || (key[0] != '_' && !ft_isalpha(key[0])))
		return (-1);
	i = 0;
	while (i < (len - 1) && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	if (i != len - 1)
		return (-1);
	if (key[i] == '+' && key[i + 1] == '=')
		return (2);
	else if ((ft_isalnum(key[i]) || key[i] == '_') && key[i + 1] == '=')
		return (1);
	else if ((ft_isalnum(key[i]) || key[i] == '_') && key[i + 1] == '\0')
		return (0);
	return (-1);
}

int	is_valid_value(char *str)
{
	int	len;
	int	ret;

	if (str == NULL || str[0] == '\0')
		return (1);
	len = ft_strlen(str);
	if ((str[0] == '"') && (str[len - 1] != '"'))
		ret = -2;
	else if ((str[0] == '\'') && (str[len - 1] != '\''))
		ret = -2;
	else if ((str[len - 1] == '"') && (str[0] != '"'))
		ret = -2;
	else if ((str[len - 1] == '\'') && (str[0] != '\''))
		ret = -2;
	else if ((str[0] == '\'' && len == 1) || \
		(str[0] == '"' && len == 1))
		ret = -2;
	else
		ret = 1;
	return (ret);
}

int	validate_key_val(char *key, char *val)
{
	int	mode;

	mode = is_valid_value(val);
	if (mode == -2)
		return (mode);
	mode = is_valid_key(key);
	return (mode);
}
