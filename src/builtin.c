/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:33:16 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/26 17:56:14 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_cd(char **argv, char **env)
{
	(void)env;
	if (ft_strstrlen(argv) > 2)
	{
		ft_putendl("cd: too many arguments");
		return (-1);
	}
	//argv[1] ? NULL : (argv[1] = getenvline(env, "HOME="));
	if((argv[1] ? chdir(argv[1]) : chdir(getenvline(env, "HOME="))) == -1)
	{
		ft_putstr("cd: bad directory: ");
		ft_putendl(argv[1]);
		return (-1);
	}
	env[casenofor(env, "OLDPWD=")] = ft_strjoin("OLDPWD=", getenvline(env, "PWD="));
	env[casenofor(env, "PWD=")] = ft_strjoin("PWD=", getcwd(NULL,0));
	return (1);
}

int		ft_setenv(char	**argv, char ***env)
{
	int i;


	if (ft_strstrlen(argv) != 3)
	{
		ft_putendl("setenv: bad usage");
		return (-1);
	}
	if((i = casenofor(*env, argv[1])) == 0)
		*env = ft_strstradd(ft_strjoin(ft_strjoin(argv[1], "="), argv[2]), *env);
	else
	{
		(*env)[i] = ft_strjoin(ft_strjoin(argv[1], "="), argv[2]);
	}
		ft_putnbr(i - 1);
	return (1);
}

int		redirectfunction(char **argv, char ***env)
{
	int result;

	result = 0;
	if(ft_strcmp("cd", argv[0]) == 0)
		result = ft_cd(argv, *env);
	if(ft_strcmp("setenv", argv[0]) == 0)
		result = ft_setenv(argv, env);/*
	if(ft_strcmp("unsetev", argv[0]) == 0)
		result = ft_unsetenv(argv, env);*/
	if(ft_strcmp("env", argv[0]) == 0)
	{
		result = 1;
		ft_putmap(*env);
	}
	return (result);
}
