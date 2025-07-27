/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_strdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:29:38 by sthiagar          #+#    #+#             */
/*   Updated: 2024/01/31 15:53:07 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_strdigit(const char *nptr)
{
	size_t	i;

	i = 0;
	if (nptr[i] == 43 || nptr[i] == 45)
		i++;
	while (i < ft_strlen(nptr))
	{
		if (!(nptr[i] >= 48 && nptr[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}
/*
int	main(void)
{
	printf("%d\n",ft_is_strdigit(" -u0"));
	return (0);
}*/
