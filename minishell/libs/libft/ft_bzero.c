/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:14:55 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/15 13:24:56 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
/*
#include <strings.h>
#include <stdio.h>
int	main(void)
{
	char	arr[5];
	size_t	i;
	size_t	num;

	num = sizeof(arr);
	//clib function
	bzero(arr,num);
	i = 0;
	while (i < num)
	{
		printf("C lib arr[%zu] is %d\n",i,arr[i]);
		i++;
	}
	printf("\n");
	//My function
	i = 0;
	while (i < num)
	{
		printf("C lib arr[%zu] is %d\n",i,arr[i]);
		i++;
	}
	return (0);
}*/
