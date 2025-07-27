/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 16:04:22 by sthiagar          #+#    #+#             */
/*   Updated: 2024/04/07 16:04:48 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_regularfile(char *dir)
{
	struct stat	filestat;

	if (stat(dir, &filestat) == -1)
		return (-1);
	else
	{
		if (S_ISREG(filestat.st_mode))
			return (1);
	}
	return (0);
}

int	is_directory(char *dir)
{
	struct stat	filestat;

	if (stat(dir, &filestat) == -1)
		return (-1);
	else
	{
		if (S_ISDIR(filestat.st_mode))
			return (1);
	}
	return (0);
}
