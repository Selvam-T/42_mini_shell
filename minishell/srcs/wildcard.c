/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emma <emma@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:56:49 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/14 21:57:08 by emma             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*get_cur_lst(int dironly, char *wc, char *str, t_var *cur_lst)
{
	char	*match;

	match = NULL;
	if (dironly && is_directory(str))
	{
		match = wildcard_match(str, wc);
		if (match)
			match = ft_strjoin(match, "/");
	}
	else if (!dironly)
	{
		match = wildcard_match(str, wc);
		if (match)
			match = ft_strdup(match);
	}
	if (match)
		ft_lstadd_back(&cur_lst, ft_lstnew(match, NULL));
	return (cur_lst);
}

char	*parse_wc(char *str, int *dironly)
{
	char	*wc;

	*dironly = 0;
	wc = ft_strdup(str);
	if (str[ft_strlen(str) - 1] == '/')
	{
		*dironly = 1;
		free(wc);
		wc = ft_substr(str, 0, ft_strlen(str) - 1);
	}
	return (wc);
}

t_var	*get_dir_entry_lst(DIR *dir, int dironly, char *wc)
{
	struct dirent	*entry;
	t_var			*cur_lst;

	cur_lst = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (!(ft_strncmp(entry->d_name, ".", 1) == 0 \
			|| ft_strncmp(entry->d_name, "..", 2) == 0))
			cur_lst = get_cur_lst(dironly, wc, entry->d_name, cur_lst);
		entry = readdir(dir);
	}
	return (cur_lst);
}

char	**get_wc_matches(char *str)
{
	char	**matched;
	DIR		*dir;
	t_var	*cur_lst;
	char	*wc;
	int		dironly;

	matched = NULL;
	cur_lst = NULL;
	wc = parse_wc(str, &dironly);
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	cur_lst = get_dir_entry_lst(dir, dironly, wc);
	free (wc);
	matched = matched_arr(cur_lst);
	free_var_lst(&cur_lst);
	if (matched == NULL)
		return (NULL);
	if (closedir(dir) == -1)
	{
		free_doubleptr(matched);
		return (NULL);
	}
	matched = sortstrarr(matched);
	return (matched);
}
