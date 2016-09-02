/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/01 11:05:18 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_strstradd(char *str, char **tab)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(tab) + 1);
	while (tab[i] != NULL)
	{
		rslt[i] = (tab[i]);
		i++;
	}
	rslt[i] = str;
	rslt[i + 1] = NULL;
	free(tab);
	return (rslt);
}

char		**ft_delemptystr(char **rslt)
{
	int i;

	i = 0;
	while (rslt[i])
	{
		if (ft_strcmp(rslt[i], "") == 0)
			rslt = ft_strstrdelone(i, rslt);
		if (rslt[i])
			rslt[i] = rmchar(rslt[i], '\\');
		i++;
	}
	return (rslt);
}

char		**argvsplit(char *av)
{
	char	**rslt;
	int		test;
	int		i;
	int		start;

	i = 0;
	test = 0;
	rslt = ft_strstrnew(1);
	while (i < (int)ft_strlen(av))
	{
		while (i < (int)ft_strlen(av) && ft_isspace(av[i]) && av[i - 1] != '\\')
			i++;
		if (av[i] == '"' && test == 0 && (test = 1))
			i++;
		else if (av[i] == '"' && test == 1 && (test = 0))
			i++;
		start = i;
		while (i < (int)ft_strlen(av) && (!ft_isspace(av[i]) || (test == 1 &&
						ft_isspace(av[i])) || (ft_isspace(av[i]) && av[i - 1] ==
						'\\' && test != 1)))
			i++;
		i = av[i - 1] == '\\' ? i += 1 : i;
		rslt = ft_strstradd(ft_strndup(av + start, i - start), rslt);
	}
	return (ft_delemptystr(rslt));
}

char		*charadd(char *str, char c)
{
	char	*rslt;
	size_t	i;
	size_t	len;

	i = 0;
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

char		**argvclean(char **argv, char **env)
{
	size_t	i;
	size_t	len;
	char	**rslt;

	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		rslt[i] = argvtest(argv[i], env);
		i++;
	}
	ft_strstrfree(argv);
	return (rslt);
}
