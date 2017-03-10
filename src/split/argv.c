/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/01 15:43:27 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "env.h"
#include "shell.h"

t_shell		*g_shell;

char		**ft_strstradd(char *str, char **table)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(table) + 1);
	if (!table)
		table = ft_strstrnew(0);
	while (table[i] != NULL)
	{
		rslt[i] = (table[i]);
		i++;
	}
	rslt[i] = str;
	rslt[i + 1] = NULL;
	free(table);
	return (rslt);
}

char		**argvsplit(char *av, char c)
{
	char	**rslt;
	int		i;
	int		start;

	i = 0;
	bzero(g_shell->quote, 2 * sizeof(int));
	rslt = NULL;
	while (av[i] && ((start = -1)))
	{
		while (av[i] && av[i] == c)
			i++;
		while (av[i] && (av[i] != c ||
					(av[i] == c && !is_reachable(av, i))))
		{
			start = (start == -1 ? i : start);
			i++;
		}
		rslt = (start != -1 ? ft_strstradd(ft_strndup(av + start, i - start),
					rslt) : rslt);
	}
	rslt = resolve_bracket(rslt);
	return (!(rslt = glob_result(rslt)) ? NULL : argvclean(rslt));
}

char		*charadd(char *str, char c)
{
	char	*rslt;
	size_t	i;
	size_t	len;

	i = 0;
	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	rslt = ft_strnew(len + 1);
	while (i < len)
	{
		rslt[i] = str[i];
		i++;
	}
	free(str);
	rslt[i] = c;
	rslt[i + 1] = '\0';
	return (rslt);
}

char		**argvclean(char **argv)
{
	size_t	i;
	size_t	len;
	size_t	merge;
	char	**rslt;

	merge = 0;
	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		if (ft_strcmp(argv[i], "~") == 0)
		{
			if (!(rslt[i - merge] = getenvline("HOME=")))
				rslt[i - merge] = ft_strdup("");
		}
		else if ((rslt[i - merge] = argvtest(argv[i])) == NULL)
			merge++;
		i++;
	}
	ft_strstrfree(argv);
	return (rslt);
}
