/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 11:17:30 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/30 17:08:42 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * HOMEDIR OK
 * PATH
 * SHLVL
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

static char		*ft_read_path(char *path)
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
	return (ft_change_c2c(result, '\n', ':'));
}

char		**init(char		**oldenv)
{
	char	**env;
	struct passwd *pw;
	char	*temp;
	char	*temp2;

	pw = getpwuid(getuid());
	env = ft_strstrnew(7);
	temp = ft_strjoin("HOME=", pw->pw_dir);
	env[1] = ft_strdup(temp);
	free(temp);
	temp = ft_strjoin("USER=", pw->pw_name);
	env[0] = ft_strdup(temp);
	free(temp);
	temp = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[2] = ft_strdup(temp);
	free(temp);
	temp2 = getenvline(oldenv, "OLDPWD");
	temp = ft_strjoin("OLDPWD=", temp2);
	env[3] = ft_strdup(temp);
	free(temp);
	free(temp2);
	temp2 = getenvline(oldenv, "TERM");
	temp = ft_strjoin("OLDPWD=", temp2);
	env[3] = ft_strdup(temp);
	free(temp);
	free(temp2);
	temp2 = ft_read_path("/etc/paths");
	temp = ft_strjoin("PATH=", temp2);
	env[4] = ft_strdup(temp);
	free(temp);
	free(temp2);
	temp2 = getenvline(oldenv, "SHLVL");
	temp = ft_strjoin("SHLVL=", temp2);
	env[5] = ft_strdup(temp);
	free(temp);
	free(temp2);
	env = ft_shlvl(env);
	return (env);
}
