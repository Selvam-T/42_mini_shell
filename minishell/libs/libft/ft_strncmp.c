/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:18:31 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/15 19:07:49 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '\0' && s2[i] == '\0') || i == n)
		return (0);
	else if (s1[i] == '\0')
		return ((unsigned char)s2[i] * -1);
	else if (s2[i] == '\0')
		return ((unsigned char)s1[i]);
	return (0);
}
/*
int	main(void)
{
	// s1 == s1 return 0 , including if s1 = s2 = '\0
	// s1 == NULL or s2 == NULL throw seg fault
	// s1 > s2 return +
	// s1 < s2 return -
	char	*s1 = "abcdefgh";
	char	*s2 = "abcdwxyz";
	int	i;

	i = ft_strncmp(s1, s2, 4);
	printf("%d %c \n",i, i);
	i = strncmp(s1, s2, 4);
	printf("%d %c \n",i, i);
	return (0);
}*/
