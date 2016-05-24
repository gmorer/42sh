/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 10:52:08 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/24 13:51:14 by gmorer           ###   ########.fr       */
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
	while(ft_strnstr(env[i], argv, n) == NULL && i < x)
		i++;
	if (i == x)
		return (NULL);
	rslt = ft_strnew(ft_strlen(env[i]) - ft_strlen(argv));
	rslt = ft_strcpy(rslt , &env[i][ft_strlen(argv)]);
	return (rslt);
}
