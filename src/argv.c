/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/30 14:57:03 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strstradd(char *str, char **tab)
{
	char **rslt;
	int i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(tab) + 1);
	while (tab[i] != NULL)
	{
		rslt[i] = (tab[i]);
		i++;
	}
	rslt[i] = str;
	i = 0;
	//free(tab);
	return (rslt);
}


char	**argvsplit(char *argv)
{
	char	**rslt;
	int		test;
	int		i;
	int		start;
	size_t	len;

	len = ft_strlen(argv);
	i = 0;
	test = 0;
	rslt = ft_strstrnew(1);
	while (i < (int)len)
	{
		while (i < (int)len && argv[i] == ' ' && argv[i - 1] != '\\')
			i++;
		if(argv[i] == '"' && test == 0 && (test = 1))
			i++;
		else if(argv[i] == '"' && test == 1 && (test = 0))
			i++;
		start = i;
		while(i < (int)len && (argv[i] != ' ' || (test == 1 && argv[i] == ' ' ) ||
					(argv[i] == ' ' && argv[i - 1] == '\\' && test != 1)))
			i++;
		if(argv[i - 1] == '\\')
			i += 1;
		rslt = ft_strstradd(ft_strndup(argv + start, i - start), rslt);
	}
	i = 0;
	while(rslt[i])
	{
		if (ft_strcmp(rslt[i], "") == 0)
			rslt = ft_strstrdelone(i, rslt);
		if (rslt[i])
		rslt[i] = rmchar(rslt[i], '\\');
		i++;
	}
	return (rslt);
}

static char	*charadd(char *str, char c)
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
	rslt[i] = c;
	rslt[i + 1] = '\0';
	return (rslt);
}

static char	*argvtest(char *str, char **env)
{
	size_t	len;
	size_t	i;
	char	*rslt;
	size_t	l;

	rslt = ft_strnew(1);
	l = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '~' && str[i - 1] != '\\' && getenvline(env, "HOME"))
			rslt = ft_strjoin(rslt, getenvline(env, "HOME="));
		else
			rslt = charadd(rslt, str[i]);
		if (str[i] == '$' && str[i + 1] && str[i - 1] != '\\')
		{
			if(str[i + 1] == '(')
			{
				while(str[i + l] && str[i + l] != ')')
					l++;
				if( getenvline(env, ft_strndup(str + i + 2, (int)l - 2)) == NULL)
				{
					ft_putendl("Undefined variable");
					return (NULL);
				}
				rslt = ft_strjoin(ft_strndup(str, (int)i) , getenvline(env, ft_strndup(str + (int)i + 2, (int)l - 2)));
				i += l;
			}
			else
			{
				l = ft_strlen(str + i);
				if( getenvline(env, ft_strndup(str + i + 1, (int)l - 1)) == NULL)
				{
					ft_putendl("Undefined variable");
					return (NULL);
				}
				rslt = ft_strjoin(ft_strndup(str, (int)i), getenvline(env, ft_strndup(str + i + 1, (int)l - 1)));
				i += l;
			}
		}/*
		if(str[i] == '\\')
			rslt = rmchar(rslt, (size_t)i);*/
		i++;
	}
	return (rslt);
}

char	**argvclean(char **argv, char **env)
{
	size_t	i;
	size_t	len;
	char **rslt;

	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		rslt[i] = argvtest(argv[i], env);
		i++;
	}
	return(rslt);
}
