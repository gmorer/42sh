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
 * PATH OkForOsx
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

	pw = getpwuid(getuid());
	env = ft_strstrnew(7);
	env[1] = ft_strjoin("HOME=", pw->pw_dir);
	env[0] = ft_strjoin("USER=", pw->pw_name);
	env[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	temp = getenvline(oldenv, "OLDPWD");
	env[3] = ft_strjoin("OLDPWD=", temp);
	free(temp);
	temp = getenvline(oldenv, "TERM");
	env[4] = ft_strjoin("OLDPWD=", temp);
	free(temp);
	temp = (LINUX ? NULL :ft_read_pathosx(OSX_PATH));
	if(temp)
	{
		env[5] = ft_strjoin("PATH=", temp);
		free(temp);
	}
	temp = getenvline(oldenv, "SHLVL");
	env[6] = ft_strjoin("SHLVL=", temp);
	free(temp);
	env = ft_shlvl(env);
	return (env);
}
