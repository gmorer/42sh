/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/04 13:32:09 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

char		**ft_strstradd(char *str, char **table)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(table) + 1);
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

char		**ft_delemptystr(char **rslt)
{
	int i;

	i = 0;
	while (rslt[i])
	{
		if (ft_strcmp(rslt[i], "") == 0)
			rslt = ft_strstrdelone(i, rslt);
		//if (rslt[i])
		//	rslt[i] = rmchar(rslt[i], '\\');
		if (!rslt[i])
			return (rslt);
		i++;
	}
	return (rslt);
}

char		**argvsplit(char *av)
{
	char	**rslt;
	int		test[2];
	int		i;
	int		start;

	start = 0;
	i = 0;
	test[0] = 0;
	test[1] = 0;
	rslt = ft_strstrnew(1);
	while (av[i])
	{
		while (av[i] && ft_isspace(av[i]))
			i++;
		if (av[i] == '\'' && test[0] == 1 && test[1] == 0)
		{
			if (i == 0 || (i > 0 && av[i - 1] != '\\'))
			{
				i++;
				test[0] = 0;
			}
		}
		else if (av[i] == '\'' && test[0] == 0 && test[1] == 0)
		{
			if (i == 0 || (i > 0 && av[i - 1] != '\\'))
			{
				start = i;
				i++;
				test[0] = 1;
			}
		}
		else if (av[i] == '"' && test[1] == 1 && test[1] == 0)
		{
			if (i == 0 || (i > 0 && av[i - 1] != '\\'))
			{
				i++;
				test[1] = 0;
			}
		}
		else if (av[i] == '"' && test[1] == 0 && test[1] == 0)
		{
			if (i == 0 || (i > 0 && av[i - 1] != '\\'))
			{
				start = i;
				i++;
				test[1] = 1;
			}
		}
		if (av[i] && !ft_isspace(av[i]) && test[0] == 0 && test[1] == 0)
			if (i == 0 || (i > 0 && av[i - 1] != '\\'))
				start = i;
		while (av[i] && ((!ft_isspace(av[i]) || (ft_isspace(av[i]) && av[i - 1] == '\\')) || test[0] == 1 || test[1] == 1))
		{
			if (av[i] == '\'' && av[i - 1] != '\\' && test[0] == 1)
				test[0] = 0;
			else if (av[i] == '"' && av[i - 1] != '\\' && test[1] == 1)
				test[1] = 0;
			else
				i++;
		}
		while (!av[i] && (test[0] == 1 || test[1] == 1))
		{/*
			ft_putstr("avant : ");
			ft_putstr(av);
			ft_putendl("<--");*/
			av = ft_quote(av, test);
			if (av[i] == '\'' || av[i] == '"')
			{
				if (i == 0 || (i > 0 && av[i - 1] != '\\'))
				{
					i++;
					//test[(av[i] == '"' ? 1 : 0)] = 0;
					test[1] = 0;
					test[0] = 0;
				}
			}
			//av = ft_strjoin(av, ft_quote(av, test));
			/*
			ft_putstr("apres : ");
			ft_putstr(av);
			ft_putendl("<--");*/
			i++;
		}
		if (start != -1)
			rslt = ft_strstradd(ft_strndup(av + start, i - start), rslt);
		start = -1;
	}
	ft_putendl("////////argvsplit://///////");
	ft_putmap(rslt);
	ft_putendl("///////////////////////////");
	return (ft_delemptystr(rslt));
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
	int		merge;
	char	**rslt;

	merge = 0;
	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		if (ft_strcmp(argv[i], "~") == 0)
		{
			if (!(rslt[i - merge] = getenvline(shell->env, "HOME=")))
				rslt[i - merge] = ft_strdup("");
		}
		else if ((rslt[i - merge] = argvtest(argv[i])) == NULL)
			merge++;
		i++;
	}
	ft_strstrfree(argv);
	return (rslt);
}
