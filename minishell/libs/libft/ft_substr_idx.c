/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_idx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:20:36 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:26:05 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//this function is same as ft_strchrind.c --> the only difference is
//this returns str+1, whereas ft_strchrind.c returns str
//replace this with other, but careful extract key function uses this,
// return value is str+1
// it returns a substr from after the 'c' if found
// sets index position to 1 after 'c' position
// if not found, index = strlen, this is important to extract key

char	*ft_substr_idx(const char *s, int c, int *ind)
{
	char	*str;

	*ind = 0;
	str = (char *)s;
	while (*str)
	{
		if (((unsigned char)*str) == ((unsigned char)c))
			return (str + 1);
		str++;
		*ind += 1;
	}
	if ((unsigned char)c == 0)
		return (str);
	return (NULL);
}
