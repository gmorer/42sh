/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 13:05:13 by acottier          #+#    #+#             */
/*   Updated: 2017/04/15 14:13:46 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

int			err_msg(char *str, int error, int type)
{
	if (type == 0)
	{
		ft_putstr("42sh: -");
		ft_putchar(str[error]);
		ft_putendl(": invalid option\ncd: usage: cd [-L|-P] [dir]");
	}
	else if (type == 1)
		ft_putendl("42sh: cd: HOME not set");
	else if (type == 2)
		ft_putendl("42sh: cd: OLDPWD not set");
	return (1);
}

int			get_opt(char **argv, int *i, int *error)
{
	int		res;
	int		j;

	*i = 1;
	res = OPT_L;
	while (argv[*i] && argv[*i][0] == '-' && argv[*i][1] != '-' && argv[*i][1])
	{
		j = 0;
		while (argv[*i][++j])
		{
			if (argv[*i][j] != 'P' && argv[*i][j] != 'L')
			{
				*error = j;
				return (BAD_OPT);
			}
		}
		if (argv[*i][j - 1] == 'P')
			res = OPT_P;
		if (argv[*i][j - 1] == 'L')
			res = OPT_L;
		(*i)++;
	}
	return (res);
}

void		replace_env(char *type, char *type2, char *content)
{
	int		i;

	if ((i = casenofor(type)) == -1)
		g_shell->env = ft_strstradd(ft_strjoin(type2, content), g_shell->env);
	else
	{
		free(g_shell->env[i]);
		g_shell->env[i] = ft_strjoin(type2, content);
	}
}

static char	*concatenate(char *path, char *pwd)
{
	char	*extract;
	char	*tmp;

	while ((extract = ft_strdupchr(path, '/')))
	{
		if (!ft_strcmp(extract, ".."))
		{
			tmp = ft_strrchr(pwd, '/');
			ft_bzero(tmp, ft_strlen(tmp));
			move_str(&path, 3, -3, ft_strlen(path));
			ft_bzero(path + ft_strlen(path) - 3, 3);
		}
		else
		{
			pwd = ft_freejoin(pwd, "/");
			pwd = ft_freejoin(pwd, extract);
			move_str(&path, ft_strlen(extract) + 1, -(ft_strlen(extract) + 1),
					ft_strlen(pwd));
		}
		ft_strdel(&extract);
	}
	if (ft_strcmp(pwd, "/"))
		pwd = ft_freejoin(pwd, "/");
	return (ft_freejoin(pwd, path));
}

char		*clear_path(char *path)
{
	char	*pwd;
	char	*res;

	pwd = getenvline("PWD=");
	if (!pwd)
		pwd = getcwd(pwd, 0);
	if (path[0] == '/')
	{
		replace_env("PWD", "PWD=", "/");
		res = path;
		ft_strdel(&pwd);
	}
	else
	{
		res = concatenate(path, pwd);
		ft_strdel(&path);
	}
	return (res);
}
