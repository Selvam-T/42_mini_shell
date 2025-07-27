/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_uc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:20:52 by sthiagar          #+#    #+#             */
/*   Updated: 2024/02/27 13:43:38 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_uc(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	char	uc;

	i = 0;
	if (n == 0)
		return (0);
	uc = (unsigned char)ft_toupper(s1[i]);
	while (i < n && s1[i] && s2[i])
	{
		if (uc != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		uc = (unsigned char)ft_toupper(s1[i]);
	}
	if ((uc == '\0' && s2[i] == '\0') || i == n)
		return (0);
	else if (uc == '\0')
		return ((unsigned char)s2[i] * -1);
	else if (s2[i] == '\0')
		return (uc);
	return (0);
}
/*
int	main()
{
	int c = ft_strncmp_uc("ab2", "AB2", 5);
	printf("c is %d\n",c);
	return (0);
}*/
