/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbef_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:49:28 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:24:44 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//this function is the opposite of ft_strchr
//get substr until before char c
//if s == NULL, return NULL
//if c not found return NULL
//if c found, return str 0 to < index of c

char	*ft_strbef_chr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (((unsigned char)str[i]) == ((unsigned char)c))
			return (ft_substr(str, 0, i));
		i++;
	}
	if ((unsigned char)c == 0)
		return (str);
	return (NULL);
}
/*
int	main()
{
	printf("%s\n",ft_strbef_chr("APPLECOON",'P'));
	return (0);
}*/
