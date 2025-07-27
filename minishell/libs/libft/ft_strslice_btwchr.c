/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslice_btwchr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:42:12 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/15 02:20:45 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//chrcount() - updates start index
//	-count chars between, exclude enclosing c itself on both ends
//ft_strslice() mallocs for chrcount, returns str
//if str == NULL return NULL
//if str has 0 or 1 c only return NULL
//if str has 2 or more c, it returns substr between first pair of c

int	chrcount(char *str, char c, int	*start)
{
	int	i;
	int	flag;
	int	count;

	if (str == NULL || ft_strlen(str) <= 0)
		return (0);
	i = 0;
	flag = -1;
	count = -1;
	while (str[i] && flag != 0)
	{
		if (str[i] == c && flag != 1)
		{
			flag = 1;
			*start = i;
		}
		else if (str[i] == c && flag == 1)
			flag = 0;
		if (flag == 1)
			count++;
		i++;
	}
	if ((flag == 1) || (flag == -1))
		return (0);
	return (count);
}

char	*ft_strslice_btwchr(char *str, char c)
{
	int		start;
	int		count;
	char	*slice;

	start = 0;
	count = chrcount(str, c, &start);
	if (count <= 0)
		return (NULL);
	slice = ft_substr(str, start + 1, count);
	return (slice);
}
