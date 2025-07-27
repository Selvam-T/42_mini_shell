/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:09 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/14 12:51:55 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ret_len(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	i = 0;
	ret = malloc(sizeof(char *) * (ret_len(s, c) + 1));
	if (!ret)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s != c && *s && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			s++;
	}
	ret[i] = 0;
	return (ret);
}

// static int	word_count(char const *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (s != NULL && *s)
// 	{
// 		if (*s == c)
// 			s++;
// 		else
// 		{
// 			i++;
// 			s = ft_strchr(s, c);
// 		}
// 	}
// 	return (i);
// }

// static char	**free_arr(char **arr, size_t i)
// {
// 	while (i--)
// 		free (arr[i]);
// 	free (arr);
// 	return (NULL);
// }

// char	**ft_split(char const *s, char c)
// {
// 	size_t		i;
// 	char		**arr;
// 	char const	*start;

// 	i = 0;
// 	arr = ft_calloc(word_count(s, c) + 1, sizeof(char *));
// 	if (arr == NULL || !s)
// 		return (NULL);
// 	while (s != NULL && *s)
// 	{
// 		if (*s != c)
// 		{
// 			start = s;
// 			s = ft_strchr(s, c);
// 			if (s == NULL)
// 				s = start + ft_strlen(start);
// 			arr[i++] = ft_substr(start, 0, s - start);
// 			if (arr[i - 1] == NULL)
// 				return (free_arr(arr, i));
// 		}
// 		else
// 			s++;
// 	}
// 	arr[i] = NULL;
// 	return (arr);
// }
/*
int	main (void)
{
	char	**s;
	//s = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^');
	//s = ft_split("\11\11\11\11hello!\11\11\11\11", '\11');
	//s = ft_split("", 'a');
	//s = ft_split("ggggggggggg", 'g');
	//s = ft_split("nonempty", '\0');
	//s = ft_split("nonempty", NULL);
	s = ft_split("hello!", 32:' ');
	//s = ft_split("one+two+three", '+');
	while (**s != '\0')
	{
		printf("%s \n",*s);
		s++;
	}
	return (0);
}*/
