/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:24:34 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/17 15:50:56 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*arr;
	size_t	s_len;

	s_len = ft_strlen(s);
	arr = (char *)malloc(1 + s_len * sizeof(char));
	if (arr == NULL)
		return (NULL);
	else
	{
		ft_memcpy(arr, s, s_len);
		arr[s_len] = '\0';
	}
	return (arr);
}
/*
int	main(void)
{
	char	*arr;
	size_t	i;

	i = 0;
	//arr = ft_strdup("12345");
	arr = strdup("12345");
	while (i < ft_strlen(arr))
	{
		printf("arr[%zu]: %c %d\n",i, arr[i], arr[i]);
		i++;
	}
	printf("arr[%zu]: %c %d\n",i, arr[i], arr[i]);
	free (arr);
	return (0);
}*/
