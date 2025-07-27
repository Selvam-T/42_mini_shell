/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:51:12 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/07 21:51:20 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_head_tail_stars(char *wildcard, int *head_star, int *tail_star)
{
	if (wildcard[0] == '*')
		*head_star = 1;
	else
		*head_star = 0;
	if (wildcard[ft_strlen(wildcard) - 1] == '*')
		*tail_star = 1;
	else
		*tail_star = 0;
}

char	*ft_strchr_headpart(char *str, char *substr, int *i)
{
	int	j;

	*i += 1;
	if (ft_strlen(str) < ft_strlen(substr))
		return (NULL);
	j = 0;
	while (substr[j] != '\0' && str[j] == substr[j])
		j++;
	if (substr[j] == '\0')
		return (str + ft_strlen(substr));
	return (NULL);
}

char	*ft_strchr_tailpart(char *str, char *substr, int *i)
{
	char	*h;
	char	*n;

	*i += 1;
	if (*substr == '\0')
		return (str);
	if (ft_strlen(str) < ft_strlen(substr))
		return (NULL);
	while (*str)
	{
		h = str;
		n = substr;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return (str + ft_strlen(substr));
		str++;
	}
	return (NULL);
}

char	*wildcard_match(char *name, char *wildcard)
{
	char	*matched;
	char	**substrs;
	int		head_star;
	int		tail_star;
	int		i;

	update_head_tail_stars(wildcard, &head_star, &tail_star);
	if (head_star && ft_strlen(wildcard) == 1)
		return (name);
	matched = name;
	substrs = ft_split(wildcard, '*');
	i = 0;
	if (!head_star)
		matched = ft_strchr_headpart(matched, substrs[i], &i);
	while (substrs[i] != NULL && matched != NULL)
		matched = ft_strchr_tailpart(matched, substrs[i], &i);
	if (matched != NULL && (matched[0] == '\0' || tail_star))
	{
		free_doubleptr(substrs);
		return (name);
	}
	free_doubleptr(substrs);
	return (NULL);
}
