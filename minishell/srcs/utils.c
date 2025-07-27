/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:44:06 by emma              #+#    #+#             */
/*   Updated: 2024/04/15 02:02:46 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_ret_null(char *str)
{
	printf("%s\n", str);
	return (NULL);
}

int	print_errmsg(char *s1, char *ptr, char *s3)
{
	if (!ptr)
	{
		ft_putstr_fd(s1, STDERR_FILENO);
		return (0);
	}
	ptr = ft_strjoin(s1, ptr);
	ptr = ft_strjoin3(ptr, s3);
	ft_putstr_fd(ptr, STDERR_FILENO);
	free_with_ptr((void **)&ptr);
	return (0);
}

int	count_doubleptr_len(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}

void	ft_argscat(char ***dst, char **src)
{
	int		i;
	int		j;
	char	**ret;

	i = -1;
	j = 0;
	if (!dst || !*dst)
		return ;
	ret = *dst;
	while (ret[j])
		j++;
	while (src[++i])
		ret[i + j] = ft_strdup(src[i]);
	ret[i + j] = NULL;
}

char	**ft_argsjoin(char **args1, char **args2)
{
	int		len1;
	int		len2;
	char	**ret;

	if (!args1)
	{
		args1 = malloc(sizeof(char *));
		args1[0] = NULL;
	}
	len1 = count_doubleptr_len(args1);
	len2 = count_doubleptr_len(args2);
	ret = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	ret[0] = NULL;
	ft_argscat(&ret, args1);
	ft_argscat(&ret, args2);
	free_doubleptr(args1);
	return (ret);
}
