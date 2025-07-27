/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:56:48 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:25:13 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//same as ft_strchr.c, additionally give index of c
//if s is NULL, return NULL, index = 0
//if c is not found, return NULL, index = s_len
//if c is found, return substr from 'c', index = index after 'c'

char	*ft_strchrind(const char *s, int c, int *ind)
{
	char	*str;

	*ind = 0;
	str = (char *)s;
	while (*str)
	{
		if (((unsigned char)*str) == ((unsigned char)c))
			return (str);
		str++;
		*ind += 1;
	}
	if ((unsigned char)c == 0)
		return (str);
	return (NULL);
}
