/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:17:59 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/04 15:33:52 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "shell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

/*
** HOMEDIR OK
** PATH OkForOsx OkForLinux
** SHLVL OK
** TERM
** USER OK
** PWD OK
** OLDPWD OK
*/

t_shell *g_shell;

static char		*ft_change_c2c(char *str, char c1, char c2)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		str[i] = (str[i] == c1 ? c2 : str[i]);
		i++;
	}
	return (str);
}

static char		*ft_read_pathlinux(char *path)
{
	int		fd;
	char	*temp;
	char	*dup;

	dup = NULL;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &temp))
	{
		if (temp && temp[0] && temp[0] != '#')
			if (ft_strstr(temp, "ENV_PATH") != NULL)
				dup = ft_strdup(temp);
		ft_strdel(&temp);
	}
	close(fd);
	if (dup)
	{
		temp = ft_strdup((ft_strstr(dup, "PATH=") + ft_strlen("PATH=")));
		ft_strdel(&dup);
		return (temp);
	}
	return (NULL);
}

static char		*ft_read_pathosx(char *path)
{
	char	*result;
	char	*temp;
	char	*temp2;
	char	*temp3;
	int		fd;

	result = NULL;
	fd = 1;
	temp2 = ft_strnew(1);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &temp))
	{
		temp3 = ft_strjoin(temp, "\n");
		result = ft_strjoin(temp2, temp3);
		ft_strdel(&temp2);
		temp2 = result;
		ft_strdel(&temp3);
		ft_strdel(&temp);
	}
	close(fd);
	return (ft_change_c2c(result, '\n', ':'));
}

char			**init_path(char **env)
{
	char			*temp;

	if (casenofor("PATH") == -1)
	{
		temp = (LINUX ? ft_read_pathlinux(LINUX_PATH) :
				ft_read_pathosx(OSX_PATH));
		if (temp)
		{
			env = ft_strstradd(ft_strjoin("PATH=", temp), env);
			ft_strdel(&temp);
		}
	}
	return (env);
}

char			**init_env(char **oldenv)
{
	char			**env;
	struct passwd	*pw;
	char			*temp;

	g_shell->env = oldenv;
	env = ft_strstrdup(oldenv);
	pw = getpwuid(getuid());
	env = init_path(env);
	if (casenofor("HOME") == -1)
		env = ft_strstradd(ft_strjoin("HOME=", pw->pw_dir), env);
	if (casenofor("USER") == -1)
		env = ft_strstradd(ft_strjoin("USER=", pw->pw_name), env);
	if (casenofor("PWD") == -1 && (temp = getcwd(NULL, 0)))
	{
		env = ft_strstradd(ft_strjoin("PWD=", temp), env);
		ft_strdel(&temp);
	}
	if (casenofor("TERM") == -1)
		env = ft_strstradd(ft_strjoin("TERM=", "xterm-256color"), env);
	env = ft_shlvl(env);
	return (env);
}
