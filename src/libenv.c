/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:52:08 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/26 17:35:44 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		casenofor(char **env, char *argv)
{
	int	rslt;
	size_t n;

	n = ft_strlen(argv);
	rslt = 0;
	while(env[rslt] && ft_strnstr(env[rslt], argv, n) == NULL)
		rslt++;
	if (!env[rslt])
		return (0);
	return (rslt);
}

char	*getenvline(char **env, char *argv)
{
	size_t	i;
	size_t	n;
	char	*rslt;
	size_t	x;

	x = ft_strstrlen(env);
	i = 0;
	rslt = NULL;
	n = ft_strlen(argv);
	while(i < x &&ft_strnstr(env[i], argv, n) == NULL)
		i++;
	if (i == x)
	{
		ft_putstr("bad enviroement variable: ");
		ft_putendl(argv);
		return (NULL);
	}
	if(argv[n - 1] != '=')
		n += 1;
	rslt = ft_strnew(ft_strlen(env[i]) - n);
	rslt = ft_strcpy(rslt , &env[i][n]);
	return (rslt);
}

char	*rmno(char *str, int x)
{
	int i;

	//ft_putendl(str);
	i = x;
	while (str[i])
	{
		str[i] = str[i + 1];
	i++;
	}
	//str[i - 1] = '\0';
	//ft_putendl(str);
	return (str);
}

char	*rmchar(char *str, char c)
{
	int i;

	(void)c;
	i = 0;
	while (str[i])
	{
		if(str[i] == '\\' && str[i - 1] == '\\' && str[i + 1] == '\\')
		{
			str = rmno(str, i);
		}
		else if(str[i] == '\\')
		{
			if(str[i + 1] == 'n')
			{
				str = rmno(str, i);
				str[i] = '\n';
			}
			else
			{
				str = rmno(str, i);
				str = rmno(str, i);
			}
		}
		if(str[i] == '"' && str[i - 1] != '\\' && str[i + 1] != '\\')
			str = rmno(str, i);
		i++;
	}
	return (str);

	
	
	
	/*
	size_t	n;
	size_t	rm;

	n = 0;
	rm = 0;
	while (str[n + rm])
	{
		if(str[n + rm] == c && str[n + rm - 1] != '\\')
			rm++;
		str[n] = str[n + rm];
		n++;
	}
	if (rm > 0)
		str[n] = '\0';
	return (str);*/
}
