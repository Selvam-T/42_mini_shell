/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:31:42 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/15 13:21:11 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i ++;
	}
	return (dest);
}
/*
int	main(void) // for int array
{
	int dest1[5];
	int src1[] = {1, 2, 3, 4, 5};
	int dest2[5];
	int src2[] = {1, 2, 3, 4, 5};
	size_t n = 5;

	//c lib function test
	memcpy(dest1,src1,n * sizeof(int));
	//my function test
	ft_memcpy(dest2,src2,n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
	printf("memcpy dest: %d | ft_memcpy dest: %d \n",dest1[i],dest2[i]);
	}
	return (0);
	}

int	main(void) // for char array
{
	char dest1[20];
	char *src1 = "This is good";
	char dest2[20];
	char *src2 = "This is good";
	int	n = 10;

	//c lib function test
	memcpy(dest1,src1,n * sizeof(char));
	//my function test
	ft_memcpy(dest2,src2,n * sizeof(char));
	printf("n is %d \n",n);
	for (int i = 0; i < n; i++)
	{
		printf("memcpy dest: %c | ft_memcpy dest: %c \n",dest1[i],dest2[i]);
	}
	return (0);
}*/
