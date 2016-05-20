/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 10:58:14 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/12 15:26:13 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strstrlen(char **c)
{
	size_t i;

	i = 0;
	while (c[i] != NULL)
		i++;
	return (i);
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
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
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

char	**ft_strstrdup(char **tab)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(tab));
	while (tab[i] != NULL)
	{
		rslt[i] = ft_strdup(tab[i]);
		i++;
	}
	rslt[i] = NULL;
	i = 0;
	return (rslt);
}

char	**ft_strstrdelfirst(char **c)
{
	int	i;

	i = 1;
	free(c[0]);
	while (c[i] != NULL)
	{
		c[i - 1] = c[i];
		i++;
	}
	c[i - 1] = NULL;
	return (c);
}
