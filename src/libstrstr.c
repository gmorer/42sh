/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:58:14 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/23 17:10:08 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strstrlen(char **c)
{
	size_t i;

	i = 0;
	if (!c)
		return (i);
	while (c[i] != NULL)
		i++;
	return (i);
}

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

	i1 = 0;
	i2 = 0;
	if (!s1 && !s2)
	{
		//ft_putendl("ft_strstrjoin 2 arg NULL");
		return (NULL);
	}
	if (!s2)
	{
		//ft_putendl("ft_strstrjoin : s2 = NULL");
		rslt = ft_strstrdup(s1);
		ft_strstrfree(s1);
		return (rslt);
	}
	if (!s1)
	{
		//ft_putendl("ft_strstrjoin : s1 = NULL");
		rslt = ft_strstrdup(s2);
		ft_strstrfree(s2);
		return (rslt);
	}
	rslt = ft_strstrnew(ft_strstrlen(s1) + ft_strstrlen(s2) + 1);
	while (s1[i1] != NULL)
	{
		rslt[i1] = s1[i1];
		i1++;
	}
	while (s2[i2] != NULL)
	{
		rslt[i1 + i2] = s2[i2];
		i2++;
	}
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
