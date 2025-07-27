/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:57:25 by sthiagar          #+#    #+#             */
/*   Updated: 2024/03/04 11:58:02 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_exp_list(char **arr)
{
	int		i;
	int		index;
	char	*key;
	char	*value;
	char	**ptr;

	ptr = sortstrarr(arr);
	i = 0;
	while (ptr[i] != NULL)
	{
		value = ft_substr_idx(ptr[i], '=', &index);
		key = ft_substr(ptr[i], 0, index + 1);
		if (index == (int)ft_strlen(ptr[i]))
			printf("declare -x %s\n", ptr[i]);
		else
			printf("declare -x %s\"%s\"\n", key, value);
		free_str(&key);
		i++;
	}
	return (0);
}

char	**get_key_value(char *str, int *mode)
{
	int		index;
	char	**pair;
	char	*temp;

	pair = malloc(sizeof(char *) * 3);
	if (pair == NULL)
		return (NULL);
	pair[1] = ft_strdup(ft_substr_idx(str, '=', &index));
	pair[0] = ft_substr(str, 0, index + 1);
	pair[2] = NULL;
	*mode = validate_key_val(pair[0], pair[1]);
	if (*mode == 2)
	{
		temp = ft_substr(pair[0], 0, ft_strlen(pair[0]) - 2);
		free_str(&pair[0]);
		pair[0] = temp;
		temp = ft_strjoin(pair[0], "=");
		free_str(&pair[0]);
		pair[0] = temp;
	}
	return (pair);
}

int	export_err_handle(int mode, char *str, int print)
{
	if (!print)
		return (1);
	if (mode == -1)
		print_errmsg("minishell: export: '", str,
			"': not a valid identifier\n");
	else if (mode == -2)
		print_errmsg("bash: export: invalid value \n", NULL, NULL);
	return (1);
}

int	execute_export(t_minishell *ms, char **args, int print)
{
	int		i;
	char	**pair;
	int		mode;
	int		exit_status;

	exit_status = 0;
	mode = 0;
	pair = NULL;
	if (args == NULL || args[0] == NULL)
		return (display_exp_list(ms->env));
	i = -1;
	while (args[++i] != NULL)
	{
		pair = get_key_value(args[i], &mode);
		if (pair == NULL)
			return (1);
		if (mode == 0 || mode == 1)
			exit_status = add_env(ms, pair[0], pair[1]);
		else if (mode == 2)
			exit_status = add_apn_env(ms, pair[0], pair[1]);
		else if (mode == -1 || mode == -2)
			exit_status = export_err_handle(mode, pair[0], print);
		free_doubleptr(pair);
	}
	return (exit_status);
}
