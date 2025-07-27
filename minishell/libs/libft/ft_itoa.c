/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emsung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:53:28 by emsung            #+#    #+#             */
/*   Updated: 2023/09/12 17:49:42 by emsung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count++;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	n_tmp;
	int		len;
	char	*ret;

	n_tmp = (long)n;
	len = count_len(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n == 0)
		ret[0] = '0';
	n_tmp = (long)n;
	if (n < 0)
	{
		ret[0] = '-';
		n_tmp *= -1;
	}
	while (n_tmp)
	{
		ret[--len] = (n_tmp % 10) + '0';
		n_tmp /= 10;
	}
	return (ret);
}
