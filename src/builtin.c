/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:33:16 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/23 17:33:29 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int		ft_cd(char **argv, char **env)
{
	(void)env;
	ft_putendl("enter in cd");
	if (ft_strstrlen(argv) > 4)
	{
		ft_putendl("cd: too many arguments");
		return (-1);
	}
	if(chdir(argv[1]) == -1)
	{
		return (-1);
	}
	ft_putendl("cd ok");
	return (1);
}

int		redirectfunction(char **argv, char **env)
{
	int result;

	ft_putendl("enter in redirectfunction");
	result = 0;
	if(ft_strcmp("cd", argv[0]) == 0)
		result = ft_cd(argv, env);/*
	if(ft_strcmp("setenv", argv[0]) == 0)
		result = ft_setenv(argv, env);
	if(ft_strcmp("unsetev", argv[0]) == 0)
		result = ft_unsetenv(argv, env);
	if(ft_strcmp("env", argv[0]) == 0)
		result = ft_env(argv, env);*/
	return (result);
}

