/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:01:27 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/12 20:09:59 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}
/*
#include <ctype.h>

int     main(int argc, char* argv[])
{
        if (argc == 2)
	{
                printf("%d\n",ft_isdigit(argv[1][0]));
		printf("%d\n",isdigit(argv[1][0]));
	}
        return (0);
}*/
