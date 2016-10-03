/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:52:08 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/01 17:55:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				casenofor(char **env, char *argv)
{
	int		rslt;
	size_t	n;

	//ft_putendl("lol1");
	if (!env || !argv)
		return(-1);
	//ft_putendl("lol2");
	n = ft_strlen(argv);
	rslt = 0;
	//	ft_putendl(env[rslt]);
	//	ft_putendl("compare to ");
	//	ft_putendl(argv);
	//ft_putendl("lol3");
	while (env[rslt] && ft_strnstr(env[rslt], argv, n) == NULL)
	{
	//	ft_putendl(env[rslt]);
	//	ft_putendl("compare to ");
	//	ft_putendl(argv);
		rslt++;
	}
	//ft_putendl("lol4");
	if (!env[rslt])
		return (-1);
	//ft_putendl("lol5");
	return (rslt);
}

static int		envtest(char *str, char *test)
{
	size_t	len;
	char	*tmp;
	int		i;

	i = 0;
	len = ft_strlen(str);
	while (test[i] && test[i] != '=')
		i++;
	if (str[ft_strlen(str) - 1] == '=')
		i++;
	tmp = ft_strndup(test, i);
	if (ft_strcmp(tmp, str) == 0)
	{
		free(tmp);
		return (1);
	}
	else
	{
		free(tmp);
		return (0);
	}
}

char			*getenvline(char **env, char *argv)
{
	size_t	i;
	size_t	n;
	char	*rslt;
	size_t	x;

	x = ft_strstrlen(env);
	i = 0;
	rslt = NULL;
	if(!argv || !x || !env)
		return (NULL);
	n = ft_strlen(argv);
	while (i < x && envtest(argv, env[i]) == 0)
		i++;
	if (i == x)
	{
		return (NULL);
	}
	if (argv[n - 1] != '=')
		n += 1;
	rslt = ft_strnew(ft_strlen(env[i]) - n);
	rslt = ft_strcpy(rslt, &env[i][n]);
	return (rslt);
}

static char		*rmno(char *str, int x)
{
	int i;

	i = x;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

char			*rmchar(char *str, char c)
{
	int i;

	(void)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i - 1] == '\\' && str[i + 1] == '\\')
			str = rmno(str, i);
		else if (str[i] == '\\')
		{
			if (str[i + 1] == 'n')
				str = rmno(str, i);
			if (str[i + 1] == 'n')
				str[i] = '\n';
			else
			{
				str = rmno(str, i);
				str = rmno(str, i);
			}
		}
		if (str[i] == '"' && str[i - 1] != '\\' && str[i + 1] != '\\')
			str = rmno(str, i);
		i++;
	}
	return (str);
}
