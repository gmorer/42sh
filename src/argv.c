/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/02 13:03:37 by gmorer           ###   ########.fr       */
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
	rslt[i + 1] = NULL;
	//ft_strstrfree(tab);
	free(tab);
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
	free(str);
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
	char	*temp;
	char	*temp2;

	rslt = ft_strnew(1);
	l = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		temp = getenvline(env, "HOME=");
		if (str[i] == '~' && str[i - 1] != '\\')
		{
		if(!temp)
		{
			ft_putendl("No $home variable set.");
			return(ft_strdup(""));
		}
			temp2 = ft_strdup(rslt);
			free(rslt);
			rslt = ft_strjoin(temp2, temp);
			free(temp2);
		}
			else
			rslt = charadd(rslt, str[i]);
			free(temp);
		if ((i < 2 && str[i] == '$' && str[i + 1]) ||(i > 1 && str[i] == '$' &&
					str[i + 1] && str[i - 1] != '\\'))
		{
			if(str[i + 1] == '(')
			{
				while(str[i + l] && str[i + l] != ')')
					l++;
				temp2 = ft_strndup(str + (int)i + 2, (int)l - 2);
				temp = getenvline(env, temp2);
				free(temp2);
				if(temp == NULL)
				{
					ft_putendl("Undefined variable");
					return (NULL);
				}
				free(rslt);
				temp2 = ft_strndup(str, (int)i);
				rslt = ft_strjoin(temp2 , temp);
				free(temp2);
				free(temp);
				i += l;
			}
			else
			{
				l = ft_strlen(str + i);
				temp2 = ft_strndup(str + i + 1, (int)l - 1);
				temp = getenvline(env, temp2);
				free(temp2);
				if(temp == NULL)
				{
					ft_putendl("Undefined variable");
					return (NULL);
				}
				free(rslt);
				temp2 = ft_strndup(str, (int)i);
				rslt = ft_strjoin(temp2, temp);
				free(temp2);
				free(temp);
				i += l;
			}
		}
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
	ft_strstrfree(argv);
	return(rslt);
}
