/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:25:08 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/21 11:25:19 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//strjoin2 is a modification of strjoin
//strjoin2 frees s1 and s2 after joining s1 and s2
//The modification is in arguments 
//arguments are char * instead of char const *
//because free() cannot free char const pointer.

char	*ft_strjoin2(char *s1, char *s2)
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
	free (s2);
	s2 = NULL;
	return (arr);
}
