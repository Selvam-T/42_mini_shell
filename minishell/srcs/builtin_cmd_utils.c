/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:20:57 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/08 10:21:02 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_last_idxofchar(char *str, char c)
{
	int	i;
	int	index;

	index = -1;
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			index = i;
	}
	return (index);
}

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args != NULL && args[i])
		i++;
	return (i);
}

char	**matched_arr(t_var *match)
{
	char	**arr;
	int		len;
	int		i;

	arr = NULL;
	len = ft_lstsize(match);
	arr = malloc(sizeof(char *) * (len + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = match->name;
		i++;
		match = match->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	arr_swap_values(char **arg1, char **arg2)
{
	char	*temp;

	temp = *arg1;
	*arg1 = *arg2;
	*arg2 = temp;
}

char	**sortstrarr(char **arg)
{
	size_t	n;
	int		length;
	int		i;
	int		j;

	length = args_count(arg);
	i = 0;
	while (i < length - 1)
	{
		j = 0;
		while (j < length - 1)
		{
			n = ft_strlen(arg[j]);
			if (ft_strlen(arg[j + 1]) > ft_strlen(arg[j]))
				n = ft_strlen(arg[j + 1]);
			if ((ft_strncmp(arg[j], arg[j + 1], n) > 0))
				arr_swap_values(&arg[j], &arg[j + 1]);
			j++;
		}
		i++;
	}
	return (arg);
}
