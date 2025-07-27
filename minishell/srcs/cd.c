/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthiagar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:39:19 by sthiagar          #+#    #+#             */
/*   Updated: 2024/02/28 15:40:36 by sthiagar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd(void)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * 1024);
	if (pwd == NULL)
		return (NULL);
	if (getcwd(pwd, 1024) != NULL)
		return (pwd);
	return (NULL);
}

int	set_cwd(char **env, char *curpwd)
{
	char	*update;
	char	*cwd;

	update = update_env(env, "OLDPWD=", curpwd);
	if (!update)
		return (1);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	update = update_env(env, "PWD=", cwd);
	free(cwd);
	if (!update)
		return (1);
	return (0);
}

int	cd_dir_err_handle(char *dir, char *msg, int print)
{
	if (!print)
		return (1);
	if (is_regularfile(dir) == 1)
		print_errmsg("minishell: cd: ", msg, ": Not a directory\n");
	else
		print_errmsg("minishell: cd: ", msg, ": No such file or directory\n");
	return (1);
}

int	cd_dir(t_minishell *ms, char *dir, char *msg, int print)
{
	char	*pwd;
	int		ret;

	ret = 0;
	pwd = get_cwd();
	if (!pwd)
	{
		free_str(&dir);
		return (1);
	}
	if (chdir(dir) == -1)
		ret = cd_dir_err_handle(dir, msg, print);
	else
	{
		if (set_cwd(ms->env, pwd) == 1)
			ret = 1;
	}
	free (pwd);
	free_str(&dir);
	return (ret);
}

int	execute_cd(t_minishell *ms, char **args, int print)
{
	char	*newdir;
	char	*str;

	if (args_count(args) > 1)
	{
		if (print)
			print_errmsg("minishell: cd: too many arguments\n", NULL, NULL);
		return (1);
	}
	else if (args == NULL || args[0] == NULL || ft_is_strequal(args[0], "~"))
	{
		newdir = get_env_value(ms->env, "HOME");
		return (cd_dir(ms, newdir, NULL, print));
	}
	else if (args[0][0] == '~')
	{
		str = ft_strdup(args[0] + 1);
		newdir = ft_strjoin("/home/", str);
		free_str(&str);
	}
	else if (ft_is_strequal(args[0], "-"))
		newdir = get_env_value(ms->env, "OLDPWD");
	else
		newdir = ft_strdup(args[0]);
	return (cd_dir(ms, newdir, args[0], print));
}
