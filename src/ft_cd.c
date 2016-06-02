/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:20:25 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/02 17:44:55 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cdok(char ***env, char *oldpwd)
{
	char	*temp;
	int		i;

	ft_putendl("ok1");
	if((i = casenofor(*env, "OLDPWD=")) == -1 && oldpwd)
		*env = ft_strstradd(ft_strjoin("OLDPWD=", oldpwd), *env);
	else if (oldpwd && i != -1)
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin("OLDPWD=", oldpwd);
	}
	temp = getcwd(NULL, 0);
	if((i = casenofor(*env, "PWD=")) == -1)
		*env = ft_strstradd(ft_strjoin("PWD=", temp), *env);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin("PWD=", temp);
	}
	free(temp);
	free(oldpwd);
	ft_putendl("ok2");
}


int		ft_cd(char **argv, char ***env)
{
	char	*temp;
	char	*oldpwd;

	if (ft_strstrlen(argv) > 2)
		ft_putendl("cd: too many arguments");
	if (ft_strstrlen(argv) > 2)
		return (-1);
	if((temp = getenvline(*env, "HOME=")) != NULL)
	{
	oldpwd = getenvline(*env, "PWD=");
	if(!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if((argv[1] ? chdir(argv[1]) : chdir(temp)) == -1)
	{
		free(oldpwd);
		free(temp);
		ft_putstr("cd: bad directory: ");
		ft_putendl(argv[1]);
		return (1);
	}
	free(temp);
	ft_cdok(env, oldpwd);
	return (0);
	}
	ft_putstr("cd: No home directory.");
	return (1);
}
