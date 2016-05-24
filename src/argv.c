/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 15:40:50 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/24 17:23:15 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*charadd(char *str, char c)
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

char	*argvtest(char *str, char **env)
{
	size_t	len;
	size_t	i;
	size_t	finallen;
	char	*rslt;

	rslt = ft_strnew(1);
	finallen = 0;
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '~')
			rslt = ft_strjoin(rslt, getenvline(env, "HOME="));
		else
			rslt = charadd(rslt, str[i]);
		i++;
	}
	return (rslt);
}

char	**argvclean(char **argv, char **env)
{
	size_t	i;
	size_t	len;;
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
