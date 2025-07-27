/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:31:04 by sthiagar          #+#    #+#             */
/*   Updated: 2023/09/19 10:43:55 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	s1len;
	size_t	s2len;

	arr = NULL;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	arr = (char *)ft_calloc((s1len + s2len + 1), sizeof(char));
	if (arr == NULL)
		return (NULL);
	ft_memcpy(arr, s1, s1len);
	ft_memcpy(&arr[s1len], s2, s2len);
	return (arr);
}
/*
int	main(void)
{
	char *arr;
	//char const *s1 = "abc";
	//char const *s2 = "";
	char *s1 = "  \t \t \n   \n\n\n\t";
 	char *s2 = "";

	arr = ft_strjoin(s1, s2);
	printf("%s \n",arr);
	printf("%d \n",arr[ft_strlen(arr)]);
	return(0);
}*/
