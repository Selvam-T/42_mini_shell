/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_conv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:27:08 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/15 10:27:27 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_struct_chr(t_var *lst)
{
	char	*arr;
	int		len;
	int		i;

	arr = NULL;
	len = ft_lstsize(lst);
	arr = (char *)ft_calloc(len + 1, sizeof(char));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < len && lst)
	{
		arr[i] = lst->c;
		lst = lst->next;
		i++;
	}
	return (arr);
}
