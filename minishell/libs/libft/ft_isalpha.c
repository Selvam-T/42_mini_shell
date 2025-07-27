/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:19:13 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/12 20:09:23 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}
/*
#include <ctype.h>

int	main(int argc, char* argv[])
{
	if (argc == 2)
	{
		printf("%d\n",ft_isalpha(argv[1][0]));
		printf("%d\n",isalpha(argv[1][0]));
	}
	return (0);
}*/
