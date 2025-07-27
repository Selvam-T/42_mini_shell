/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:27:06 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/19 21:46:12 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (((unsigned char)*str) == ((unsigned char)c))
			return (str);
		str++;
	}
	if ((unsigned char)c == 0)
		return (str);
	return (NULL);
}
/*
int	main(void)
{
	// *s == NULL return segmentation fault
	// *s == "\0" return NULL
	//
	// c = '\0' and s !=NULL return ptr to s at '\0' index
	// if no match return NULL
	// if match return s
	// check if s and c cast to unsigned char when comparing
	char *s = "$(Hell";
	int	c = '(';
	printf("%s \n",ft_strchr(s,c));
	printf("%s \n",strchr(s,c));
	return (0);
}*/
