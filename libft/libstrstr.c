/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:58:14 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/29 18:43:55 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_strstrfree(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_strstrnew(size_t i)
{
	char	**rslt;
	size_t	x;

	if (!(rslt = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	x = 0;
	while (x <= i)
		rslt[x++] = NULL;
	return (rslt);
}

char	**ft_strstrjoin(char **s1, char **s2)
{
	char	**rslt;
	int		i1;
	int		i2;

	i1 = -1;
	i2 = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s2 || !s1)
	{
		rslt = ft_strstrdup((!s1 ? s2 : s1));
		ft_strstrfree(!s1 ? s2 : s1);
		return (rslt);
	}
	rslt = ft_strstrnew(ft_strstrlen(s1) + ft_strstrlen(s2) + 1);
	while (s1[++i1] != NULL)
		rslt[i1] = s1[i1];
	while (s2[++i2] != NULL)
		rslt[i1 + i2] = s2[i2];
	free(s1);
	free(s2);
	rslt[i1 + i2 + 1] = NULL;
	return (rslt);
}

char	**ft_strstrdup(char **table)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(table));
	while (table[i] != NULL)
	{
		rslt[i] = ft_strdup(table[i]);
		i++;
	}
	rslt[i] = NULL;
	i = 0;
	return (rslt);
}

char	**ft_strstrdelone(int i, char **str)
{
	char	**rslt;
	int		y;

	y = 0;
	if (!(rslt = malloc(sizeof(char*) * ft_strstrlen(str))))
		return (NULL);
	i++;
	while (y < i)
	{
		rslt[y] = str[y];
		y++;
	}
	free(str[i - 1]);
	while (str[i])
	{
		rslt[i - 1] = str[i];
		i++;
	}
	rslt[i - 1] = NULL;
	free(str);
	return (rslt);
}
