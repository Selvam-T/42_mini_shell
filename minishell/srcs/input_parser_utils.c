/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:56:33 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/12 11:46:07 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quote_adv_idx(char *s, int *i, char c)
{
	char	*sub;
	int		j;

	if (s == NULL || s[0] == '\0' || s[*i] == '\0')
		return (NULL);
	j = ft_chrindex(&s[*i + 1], c);
	sub = ft_substr(s, *i + 1, j);
	*i = *i + j + 2;
	return (sub);
}

int	count_delim(char *str, char c)
{
	int	i;

	i = 0;
	while (str != NULL && *str)
	{
		if (*str == c)
			i++;
		str++;
	}
	if (c == '"' || c == '\'')
		return (i / 2);
	return (i);
}

int	next_delim(char *str)
{
	int	i;
	int	j;

	i = ft_chrindex(str, '"');
	j = ft_chrindex(str, '\'');
	if (i >= 0 && (j < 0 || j > i))
		return (34);
	else if (j >= 0 && (i < 0 || i > j))
		return (39);
	return (0);
}
