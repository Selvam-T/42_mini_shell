/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbef_chridx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:51:20 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:19:38 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//this function is the opposite of ft_strchr
//get substr until before char c
//if s == NULL, return NULL
//if c not found return NULL
//if c found, return str 0 to < index of c

char	*ft_strbef_chridx(const char *s, int c, int *i)
{
	char	*str;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	while (str[*i])
	{
		if (((unsigned char)str[*i]) == ((unsigned char)c))
			return (ft_substr(str, 0, *i));
		*i += 1;
	}
	if ((unsigned char)c == 0)
		return (ft_strdup(str));
	return (NULL);
}
/*
int	main()
{
	int	i;

	i = 0;
	printf("%s, %d\n",ft_strbef_chridx("APPLE+COON",'+', &i), i);
	return (0);
}*/
