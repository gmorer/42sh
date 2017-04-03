/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:52:08 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/01 15:27:06 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"

t_shell		*g_shell;

int				ft_isin(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int				casenofor(char *argv)
{
	int		rslt;
	size_t	n;

	if (!g_shell->env || !argv)
		return (-1);
	n = ft_strlen(argv);
	rslt = 0;
	while (g_shell->env[rslt] &&
			(ft_strchr(g_shell->env[rslt], '=') - g_shell->env[rslt] != (int)n
			|| ft_strncmp(g_shell->env[rslt], argv, n) != 0))
	{
		rslt++;
	}
	if (!g_shell->env[rslt])
		return (-1);
	return (rslt);
}

static int		envtest(char *str, char *test)
{
	char	*tmp;
	int		i;

	i = 0;
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

char			*getenvline(char *argv)
{
	size_t	i;
	size_t	n;
	char	*rslt;
	size_t	x;

	x = ft_strstrlen(g_shell->env);
	i = 0;
	rslt = NULL;
	if (!argv || !x || !g_shell->env)
		return (NULL);
	n = ft_strlen(argv);
	while (i < x && envtest(argv, g_shell->env[i]) == 0)
		i++;
	if (i == x)
	{
		return (NULL);
	}
	if (argv[n - 1] != '=')
		n += 1;
	rslt = ft_strnew(ft_strlen(g_shell->env[i]) - n);
	rslt = ft_strcpy(rslt, (&g_shell->env[i][n]));
	return (rslt);
}

char			*rmno(char *str, int x)
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
