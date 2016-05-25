/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:52:08 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/25 17:10:08 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		casenofor(char **env, char *argv)
{
	int	rslt;
	size_t n;

	n = ft_strlen(argv);
	rslt = 0;
	while(ft_strnstr(env[rslt], argv, n) == NULL)
		rslt++;
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

char	*rmchar(char *str, size_t i)
{
	char	*rslt;
	size_t	n;

	ft_putendl("test");
	if(ft_strlen(str) > i)
		return (NULL);
	ft_putendl("test");
	rslt = ft_strnew(ft_strlen(str));
	n = 0;
	ft_putendl("test");
	while ( n < i && str[n])
	{
		rslt[n] = str[n];
		n++;
	}
	ft_putendl("test");
	n++;
	while (str[n + 1])
	{
		rslt[n] = str[n + 1];
		n++;
	}
	ft_putendl("test");
	rslt[n] = '\0';
	return (rslt);
}
