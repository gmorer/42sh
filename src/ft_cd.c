/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:20:25 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/02 11:46:49 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cdok(char ***env, char *oldpwd)
{
	char	*temp;
	int		i;

	if ((i = casenofor(*env, "OLDPWD=")) == -1 && oldpwd)
		*env = ft_strstradd(ft_strjoin("OLDPWD=", oldpwd), *env);
	else if (oldpwd && i != -1)
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
	}
	temp = getcwd(NULL, 0);
	if ((i = casenofor(*env, "PWD=")) == -1)
		*env = ft_strstradd(ft_strjoin("PWD=", temp), *env);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin("PWD=", temp);
	}
	free(temp);
	free(oldpwd);
}

static int	ft_cdtest(char *path)
{
	struct stat path_stat;

	if (access(path, F_OK) == -1)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(path);
		return (0);
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr("ls: cannot open directory ");
		ft_putstr(path);
		ft_putendl(": Permission denied");
		return (0);
	}
	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode) == 1)
	{
		ft_putstr("cd: not a directory: ");
		ft_putendl(path);
		return (0);
	}
	chdir(path);
	return (1);
}

static int	ft_cd_find(int test, char ***env, char **argv)
{
	char *temp;

	if ((ft_strcmp(argv[1], "-") == 0))
	{
		temp = getenvline(*env, "OLDPWD=");
		test = ft_cdtest(temp);
		free(temp);
	}
	else if ((argv[1]))
		test = ft_cdtest(argv[1]);
	else if (!argv[1])
	{
		temp = getenvline(*env, "HOME=");
		if (temp)
			test = ft_cdtest(temp);
		if (temp)
			free(temp);
		else
		{
			test = 0;
			ft_putendl("cd: No home directory.");
		}
	}
	return (test);
}

int			ft_cd(char **argv, char ***env)
{
	char	*oldpwd;
	int		test;

	test = 0;
	if (ft_strstrlen(argv) > 2)
		ft_putendl("cd: too many arguments");
	if (ft_strstrlen(argv) > 2)
		return (-1);
	oldpwd = getenvline(*env, "PWD=");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	test = ft_cd_find(test, env, argv);
	if (test == 0)
	{
		free(oldpwd);
		return (1);
	}
	ft_cdok(env, oldpwd);
	return (0);
}
