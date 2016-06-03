/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:20:25 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/03 16:40:03 by gmorer           ###   ########.fr       */
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

int			ft_cd(char **argv, char ***env)
{
	char	*temp;
	char	*oldpwd;

	if (ft_strstrlen(argv) > 2)
		ft_putendl("cd: too many arguments");
	if (ft_strstrlen(argv) > 2)
		return (-1);
	if ((temp = getenvline(*env, "HOME=")) != NULL)
	{
		oldpwd = getenvline(*env, "PWD=");
		if (!oldpwd)
			oldpwd = getcwd(NULL, 0);
		if ((argv[1] ? ft_cdtest(argv[1]) : ft_cdtest(temp)) == 0)
		{
			free(oldpwd);
			free(temp);
			return (1);
		}
		free(temp);
		ft_cdok(env, oldpwd);
		return (0);
	}
	ft_putendl("cd: No home directory.");
	return (1);
}
