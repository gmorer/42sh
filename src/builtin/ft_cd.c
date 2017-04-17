/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:10:10 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:27:39 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

t_shell	*g_shell;

static int	change_dir(char *path)
{
	struct stat path_stat;

	if (access(path, F_OK) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(path);
		return (1);
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr("ls: cannot open directory ");
		ft_putstr(path);
		ft_putendl(": Permission denied");
		return (1);
	}
	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode) == 1)
	{
		ft_putstr("cd: not a directory: ");
		ft_putendl(path);
		return (1);
	}
	chdir(path);
	return (0);
}

static int	option_p(char *path)
{
	char	*newpwd;
	char	*curpwd;

	if (ft_strcmp(path, "-") == 0)
	{
		ft_strdel(&path);
		path = getenvline("OLDPWD=");
		if (!path)
			return (err_msg(NULL, 0, 2));
	}
	if (change_dir(path) == 0)
	{
		newpwd = NULL;
		newpwd = getcwd(newpwd, 0);
		curpwd = getenvline("PWD=");
		replace_env("OLDPWD", "OLDPWD=", curpwd);
		ft_strdel(&curpwd);
		replace_env("PWD", "PWD=", newpwd);
		ft_strdel(&newpwd);
		ft_strdel(&path);
		return (0);
	}
	ft_strdel(&path);
	return (1);
}

static int	option_l(char *path)
{
	struct stat	info;
	char		*curpwd;

	if (ft_strcmp(path, "-") == 0)
	{
		ft_strdel(&path);
		path = getenvline("OLDPWD=");
		if (!path)
			return (err_msg(NULL, 0, 2));
	}
	lstat(path, &info);
	if (S_ISLNK(info.st_mode))
	{
		curpwd = getenvline("PWD=");
		path = clear_path(path);
		change_dir(path);
		replace_env("OLDPWD", "OLDPWD=", curpwd);
		ft_strdel(&curpwd);
		replace_env("PWD", "PWD=", path);
		ft_strdel(&path);
		return (0);
	}
	else
		return (option_p(path));
}

static int	no_arg(void)
{
	char	*home;

	home = getenvline("HOME=");
	if (!home)
		err_msg(NULL, 0, 1);
	else
		return (option_p(home));
	return (1);
}

int			ft_cd(char **argv)
{
	int			i;
	int			option;
	int			error;

	error = 0;
	option = get_opt(argv, &i, &error);
	if (error)
		return (err_msg(argv[i], error, 0));
	if (!argv[i])
		return (no_arg());
	else if (option == OPT_P)
		return (option_p(ft_strdup(argv[i])));
	else
		return (option_l(ft_strdup(argv[i])));
	return (1);
}
