/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/22 18:05:25 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

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
	int		len;

	len = 0;
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
			{
				test[0] = 0;
			}
			else if (av[i] == '"' && av[i - 1] != '\\' && test[1] == 1)
			{
				test[1] = 0;
			}
			else
				i++;
		}
		rslt = ft_strstradd(ft_strndup(av + start, i - start), rslt);
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
	char	**rslt;

	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		if (ft_strcmp(argv[i], "~") == 0)
		{
			if (!(rslt[i] = getenvline(shell->env, "HOME=")))
				rslt[i] = ft_strdup("");
		}
		else
			rslt[i] = argvtest(argv[i]);
		i++;
	}
	ft_strstrfree(argv);
	return (rslt);
}
