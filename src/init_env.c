/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 11:17:30 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/03 11:23:58 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * HOMEDIR OK
 * PATH OkForOsx OkForLinux
 * SHLVL OK
 * TERM
 * USER OK
 * PWD OK
 * OLDPWD OK
 */

static char		*ft_change_c2c(char *str, char c1, char c2)
{
	int		i;

	i = 0;
	if(!str)
		return (NULL);
	while(str[i])
	{
		str[i] = (str[i] == c1 ? c2 : str[i]);
		i++;
	}
	return (str);
}

static char		*ft_read_pathlinux(char *path)
{
	//char	*result;
	int		fd;
	char	*temp;
	char	*dup;

	dup = NULL;
	if((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while(get_next_line(fd, &temp))
	{
		if(temp && temp[0] && temp[0] != '#')
			if (ft_strstr(temp, "ENV_PATH") != NULL)
			{
				dup = ft_strdup(temp);
			}
		free(temp);
	}
	close(fd);
	if(dup)
	{
		temp = ft_strdup((ft_strstr(dup, "PATH=")));
		free(dup);
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

	fd = 1;
	temp2 = ft_strnew(1);
	if((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &temp))
	{
		temp3 = ft_strjoin(temp, "\n");
		result = ft_strjoin(temp2, temp3);
		free(temp2);
		temp2 = result;
		free(temp3);
		free(temp);	
	}
	close(fd);
	return (ft_change_c2c(result, '\n', ':'));
}

char		**init(char		**oldenv)
{
	char	**env;
	struct passwd *pw;
	char	*temp;
	int		i;

	i = 0;
	pw = getpwuid(getuid());
	env = ft_strstrnew(9);
	env[i++] = ft_strjoin("HOME=", pw->pw_dir);
	env[i++] = ft_strjoin("USER=", pw->pw_name);
	temp = getcwd(NULL, 0);
	if(temp)
		env[i++] = ft_strjoin("PWD=", temp);
	if(temp)
		free(temp);
	temp = getenvline(oldenv, "OLDPWD");
	if (temp)	
		env[i++] = ft_strjoin("OLDPWD=", temp);
	if (temp)	
		free(temp);
	temp = getenvline(oldenv, "TERM");
	if (temp)	
		env[i++] = ft_strjoin("TERM=", temp);
	if (temp)	
		free(temp);
	temp = (LINUX ? ft_read_pathlinux(LINUX_PATH) : ft_read_pathosx(OSX_PATH));
	if(temp)
	{
		env[i++] = ft_strjoin("PATH=", temp);
		free(temp);
	}
	temp = getenvline(oldenv, "SHLVL");
	if (temp)	
		env[i++] = ft_strjoin("SHLVL=", temp);
	if (temp)	
		free(temp);
	env[i++] = ft_strdup("?=0");
	env[i++] = ft_strdup("_=minishell");
	env[i++] = NULL;
	env = ft_shlvl(env);
	return (env);
}
