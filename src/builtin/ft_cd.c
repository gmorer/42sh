/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 14:20:25 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/21 16:12:53 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

t_shell	*g_shell;

static void	ft_cdok(char *oldpwd, char *arg, int option_p)
{
	char	*temp;
	int		i;

	if ((i = casenofor("OLDPWD")) == -1 && oldpwd)
		g_shell->env = ft_strstradd(ft_strjoin("OLDPWD=", oldpwd),
				g_shell->env);
	else if (oldpwd && i != -1)
	{
		free(g_shell->env[i]);
		g_shell->env[i] = ft_strjoin("OLDPWD=", oldpwd);
	}
	temp = option_p ? ft_strjoin(oldpwd, arg) : getcwd(NULL, 0);
	if ((i = casenofor("PWD")) == -1)
		g_shell->env = ft_strstradd(ft_strjoin("PWD=", temp), g_shell->env);
	else
	{
		free(g_shell->env[i]);
		g_shell->env[i] = ft_strjoin("PWD=", temp);
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

static char	*ft_cd_find(char **argv, int opt_len)
{
	char	*temp;
	int		test;
	char	*temp2;

	test = 0;
	if ((ft_strcmp(argv[opt_len], "-") == 0) || !argv[opt_len])
	{
		temp2 = !argv[opt_len] ? "HOME" : "OLDPWD";
		temp = getenvline(temp2);
		if (!temp)
		{
			ft_putstr_fd("21sh: cd: ", 2);
			ft_putstr_fd(temp2, 2);
			ft_putendl_fd(" not set", 2);
			return (NULL);
		}
		if (ft_cdtest(temp))
			return (temp);
		free(temp);
		return (NULL);
	}
	else if ((argv[opt_len]))
		return (ft_cdtest(argv[opt_len]) ? ft_strdup(argv[opt_len]) : NULL);
	return (NULL);
}

int			cd_option(char **argv, int *option_p, int *option_l)
{
	int i;
	int	j;

	i = 1;
	*option_p = 0;
	*option_l = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		if ((j = 1) && argv[i] && !ft_strcmp(argv[i], "--"))
			return (i + 1);
		while (argv[i][++j])
		{
			*option_p = argv[i][j] == 'P' ? 1 : *option_p;
			*option_l = argv[i][j] == 'L' ? 1 : *option_l;
			if (argv[i][j] != 'P' && argv[i][j] != 'L')
			{
				ft_putstr("21sh: -");
				ft_putchar(argv[i][j]);
				ft_putendl(": invalid option\ncd: usage: cd [-L|-P] [dir]");
				return (-1);
			}
		}
		i++;
	}
	return (i);
}

int			ft_cd(char **argv)
{
	char	*oldpwd;
	char	*temp;
	int		option_p;
	int		option_l;
	int		option_len;

	if ((option_len = cd_option(argv, &option_p, &option_l)) == -1)
		return (1);
	if (ft_strstrlen(argv) - option_len > 2)
	{
		ft_putendl("cd: too many arguments");
		return (-1);
	}
	oldpwd = getenvline("PWD=");
	if (!oldpwd)
		oldpwd = getcwd(NULL, 0);
	if ((temp = ft_cd_find(argv, option_len)) == NULL)
	{
		free(oldpwd);
		return (1);
	}
	ft_cdok(oldpwd, temp, option_p);
	free(temp);
	return (0);
}
