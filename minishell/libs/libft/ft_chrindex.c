/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 10:00:49 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/17 10:07:04 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//--used in get_env_value()
//if s is NULL, return -1, c is not found
//if c is not found, return -1
//if c is found, return index of 'c'

int	ft_chrindex(const char *s, int c)
{
	int	index;

	index = 0;
	while (*s)
	{
		if (((unsigned char)*s) == ((unsigned char)c))
			return (index);
		s++;
		index += 1;
	}
	return (-1);
}
