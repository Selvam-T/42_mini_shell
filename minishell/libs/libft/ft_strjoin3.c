/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:14:19 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/21 12:14:24 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//strjoin3 has characteristics of strjoin2
//strjoin3 frees s1 only, not free s2 
//because s2 could be a substring of a fuller string
//s2 can only be freed properly in the calling function

char	*ft_strjoin3(char *s1, char *s2)
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
	free (s1);
	s1 = NULL;
	return (arr);
}
