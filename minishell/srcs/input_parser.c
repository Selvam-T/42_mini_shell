/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:49:20 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/14 21:57:20 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_substitution(t_minishell *shell, char *str, char c)
{
	char	*result;
	char	*ptr1;
	char	*ptr2;
	int		i;
	int		t;

	if (str == NULL)
		return (NULL);
	t = count_delim(str, '$');
	if (t == 0 || (c == '\''))
		return (ft_strdup(str));
	result = NULL;
	while (t-- > 0)
	{
		i = 0;
		ptr1 = ft_strbef_chridx(str, '$', &i);
		ptr2 = ft_strjoin2(ptr1, extract_id_value(shell, str, &i, &t));
		result = ft_strjoin2(result, ptr2);
		str = &str[i];
	}
	result = ft_strjoin3(result, str);
	return (result);
}

char	*part_resolved(t_minishell *shell, char *pstr, char c, int *i)
{
	char	*ptr1;
	char	*ptr2;
	char	*ptr3;

	ptr1 = ft_strbef_chridx(pstr, c, &i[1]);
	if (ft_chrindex(ptr1, '*') != -1)
		i[0] = 1;
	ptr2 = trim_quote_adv_idx(pstr, &i[1], c);
	ptr3 = variable_substitution(shell, ptr2, c);
	if (ptr2 && ptr3 && ft_strncmp(ptr2, ptr3, -1) && ft_strchr(ptr3, '*'))
		i[0] = 1;
	free_str(&ptr2);
	ptr2 = ft_strjoin2(ptr1, ptr3);
	return (ptr2);
}

char	*resolve_quote_str(t_minishell *shell, char *str, int len, int *do_wc)
{
	char	*temp;
	char	*result;
	int		i[2];
	int		c;
	int		k;

	result = NULL;
	k = 0;
	i[0] = *do_wc;
	while (k < len)
	{
		i[1] = 0;
		c = next_delim(&str[k]);
		temp = part_resolved(shell, &str[k], c, i);
		*do_wc = i[0];
		result = ft_strjoin2(result, temp);
		k += i[1];
	}
	return (result);
}

char	**no_match_ret_str(char *str)
{
	char	**ret;

	ret = malloc(sizeof(char *) * 2);
	if (ret == NULL)
		return (NULL);
	ret[0] = ft_strdup(str);
	ret[1] = NULL;
	return (ret);
}

char	**parse_argument(t_minishell *shell, char *input)
{
	char	**result;
	char	*newstr;
	int		do_wc;

	result = NULL;
	newstr = NULL;
	do_wc = 0;
	newstr = resolve_quote_str(shell, input, ft_strlen(input), &do_wc);
	if (do_wc)
	{
		result = get_wc_matches(newstr);
		if (result != NULL && result[0] == NULL)
		{
			free_doubleptr(result);
			result = no_match_ret_str(newstr);
		}
	}
	else
		result = no_match_ret_str(newstr);
	free_str(&newstr);
	return (result);
}
