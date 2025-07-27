/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslice_btwidx.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:42:53 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:21:32 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//similar to ft_substr()
//ft_substr() takes start index, and len of substring
//whereas ft_slice() takes start index and end index
char	*ft_strslice_btwidx(char *str, int start, int end)
{
	int		i;
	int		len;
	char	*slice;

	len = ft_strlen(str);
	if (len <= 0 || end - start > len)
		return (NULL);
	len = end - start + 1;
	slice = (char *)ft_calloc((len + 1), sizeof(char));
	if (slice == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		slice[i] = str[start + i];
		i++;
	}
	return (slice);
}
