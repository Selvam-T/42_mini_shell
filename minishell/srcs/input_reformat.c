/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reformat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:33:22 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/08 11:33:48 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_token(char **tokens, int *str_info, int *offset, int *len)
{
	char	*curtoken;

	while (str_info[*offset] == 0)
		*offset += 1;
	*len = str_info[*offset];
	curtoken = (char *)malloc(sizeof(char *) * (*len + 1));
	if (curtoken == NULL)
	{
		free_doubleptr(tokens);
		return (NULL);
	}
	return (curtoken);
}

char	**get_rfmt_input(char **tokens, char *str, int *str_info, int count)
{
	int		idx;
	int		offset;
	int		chr_idx;
	int		len;

	idx = 0;
	offset = 0;
	len = 0;
	while (idx < count)
	{
		tokens[idx] = alloc_token(tokens, str_info, &offset, &len);
		if (tokens[idx] == NULL)
			return (NULL);
		chr_idx = 0;
		while (chr_idx < len)
		{
			tokens[idx][chr_idx] = str[offset];
			offset++;
			chr_idx++;
		}
		tokens[idx][chr_idx] = '\0';
		idx++;
	}
	tokens[idx] = NULL;
	return (tokens);
}

char	**rfmt_input(char *input)
{
	char	**tokens;
	int		*str_info;
	int		count;
	int		length;

	tokens = NULL;
	str_info = NULL;
	length = ft_strlen(input);
	str_info = (int *)ft_calloc(length + 1, sizeof(int));
	if (str_info == NULL)
		return (NULL);
	str_info[length] = -1;
	count = 0;
	count = update_str_info(input, length, &str_info);
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);
	tokens = get_rfmt_input(tokens, input, str_info, count);
	free (str_info);
	return (tokens);
}
