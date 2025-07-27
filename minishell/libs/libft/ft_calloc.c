/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:56:22 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/17 11:22:07 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	arr = (void *)malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	else
	{
		ft_bzero(arr, nmemb * size);
		return (arr);
	}
}
/*
int	main(void)
{
	int	*arr;
	size_t	nmemb = 8539;

	arr = calloc(nmemb, sizeof(int));
	//arr = (int *)ft_calloc(nmemb,sizeof(int));

	if (arr == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	for (size_t i = 0; i < nmemb; i++)
		printf("arr[%zu]: %p \n",i, &arr[i]);
	free(arr);
}*/
