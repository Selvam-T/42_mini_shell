/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reformat_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:34:04 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/08 11:34:18 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chars(char *str)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (str[i] && (str[i] != '(' && str[i] != ')' && \
		str[i] != '|' && str[i] != '<' && str[i] != '>' && \
		str[i] != '&' && str[i] != 32))
	{
		if (str[i] == '"' || str[i] == '\'')
			flag = str[i];
		while (str[i] != '\0' && flag != 0)
		{
			if (str[i + 1] == flag)
				flag = 0;
			i += 1;
		}
		i++;
	}
	return (i);
}

int	is_splchr(char c1, char c2)
{
	int	flag;

	flag = 0;
	if (c1 == '(' || c1 == ')' || (c1 == '<' && c2 != '<') || \
		(c1 == '|' && c2 != '|') || (c1 == '>' && c2 != '>') || \
		(c1 == '&' && c2 != '&'))
		flag = 1;
	else if ((c1 == '|' && c2 == '|') || (c1 == '&' && c2 == '&') || \
		(c1 == '<' && c2 == '<') || (c1 == '>' && c2 == '>'))
		flag = 2;
	else if (c1 != 32)
		flag = 3;
	return (flag);
}

int	update_str_info(char *input, int length, int **str_info)
{
	int	splchr;
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < length)
	{
		splchr = is_splchr(input[i], input[i + 1]);
		if (splchr == 1)
			(*str_info)[i] = 1;
		else if (splchr == 2)
			(*str_info)[i] = 2;
		else if (splchr == 3)
			(*str_info)[i] = count_chars(&input[i]);
		if (splchr != 0)
		{
			i += (*str_info)[i] - 1;
			count++;
		}
		i++;
	}
	return (count);
}
