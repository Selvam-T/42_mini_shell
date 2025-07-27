/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:33:35 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/18 18:23:45 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	newlen;

	newlen = 0;
	substr = NULL;
	if (*s == '\0' || start >= ft_strlen(s))
		newlen = 0;
	else
	{
		newlen = ft_strlen(&s[start]);
		if (newlen > len)
			newlen = len;
	}
	substr = (char *)ft_calloc((1 + newlen), sizeof(char));
	if (substr == NULL)
		return (NULL);
	else
	{
		ft_memcpy(substr, &s[start], newlen);
	}
	return (substr);
}
/*
int	main(void)
{
	char *sub;
	char const *s = "hola";
	sub = ft_substr(s, 1, 2);
	printf("%s %zu\n",sub, ft_strlen(sub));
	return (0);
}*/
