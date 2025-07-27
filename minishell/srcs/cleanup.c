/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:50:18 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/18 12:50:30 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	temp_lst(t_var **lst, char *str, int size)
{
	int	j;

	j = 0;
	while (j <= size)
	{
		ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, str[j]));
		j++;
	}
	return (j);
}

int	handle_dollarquestion(t_var **lst, char *s, int i)
{
	int	count;

	count = 1;
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '"'));
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '$'));
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '?'));
	while (s[i + count] && (s[i + count] != '(' && \
		s[i + count] != ')' && s[i + count] != '|' && \
		s[i + count] != '<' && s[i + count] != '>' && \
		s[i + count] != '&' && s[i + count] != 32))
	{
		ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, s[i + count]));
		count++;
	}
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '"'));
	return (i + count);
}

int	handle_dollar(t_var **lst, char *s)
{
	int	i;

	i = 0;
	if (s[i + 1] != '\0' && s[i + 1] == 32)
	{
		ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, s[i]));
		return (i + 1);
	}
	else if (s[i + 1] != '\0' && s[i + 1] == '*')
		return (i + 2);
	else if (s[i + 1] != '\0' && s[i + 1] == '?')
		return (handle_dollarquestion(lst, s, i + 1));
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '"'));
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '$'));
	i++;
	while (s[i] != '\0' && is_valid_id_chr(s[i], 1))
	{
		ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, s[i]));
		i ++;
	}
	ft_lstadd_back(lst, ft_lstnew2(NULL, NULL, '"'));
	return (i);
}

int	handle_quote(t_var **lst, char *input, int *i)
{
	int	index;

	index = ft_chrindex(&input[*i + 1], input[*i]);
	if (index == -1)
	{
		free_var_lst(lst);
		return (-1);
	}
	*i += temp_lst(lst, &input[*i], index + 1);
	return (*i);
}

char	*clean_up_quotes(char *input)
{
	t_var	*lst;
	char	*ret;
	int		i;

	i = 0;
	lst = NULL;
	ret = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (handle_quote(&lst, input, &i) == -1)
				return (NULL);
		}
		else if (input[i] == '$')
			i += handle_dollar(&lst, &input[i]);
		else
		{
			ft_lstadd_back(&lst, ft_lstnew2(NULL, NULL, input[i]));
			i++;
		}
	}
	ret = convert_struct_chr(lst);
	free_var_lst(&lst);
	return (ret);
}
