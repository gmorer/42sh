/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:15:52 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/07 17:16:00 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*checkhomedir(char *str, char **env, int i, char *rslt)
{
	char	*temp;
	char	*temp2;

	temp = getenvline(env, "HOME=");
	if ((str[i] && str[i] == '~' && i == 0) || (str[i] && str[i] == '~' &&
				str[i - 1] != '\\'))
	{
		if (!temp)
		{
			ft_putendl("No $home variable set.");
			return (ft_strdup(""));
		}
		temp2 = ft_strdup(rslt);
		free(rslt);
		rslt = ft_strjoin(temp2, temp);
		free(temp2);
	}
	else
		rslt = charadd(rslt, str[i]);
	free(temp);
	return (rslt);
}

static int	checkvar(char *temp, char *str, char **rslt, int i)
{
	char	*temp2;

	free(*rslt);
	if (temp == NULL)
	{
		ft_putendl("Undefined variable");
		return (0);
	}
	temp2 = ft_strndup(str, (int)i);
	*rslt = ft_strjoin(temp2, temp);
	free(temp);
	free(temp2);
	return (1);
}

static int	withbracket(size_t *i, char **rslt, char **env, char *str)
{
	int		l;
	char	*temp2;

	l = 0;
	while (str[*i + l] && str[*i + l] != ')')
		l++;
	temp2 = ft_strndup(str + (int)*i + 2, (int)l - 2);
	if (checkvar(getenvline(env, temp2), str, rslt, *i) == 0)
	{
		free(temp2);
		return (0);
	}
	free(temp2);
	*i += l;
	return (1);
}

char		*argvtest1(char *str, char **env, char *rslt, size_t i)
{
	char	*temp2;

	while (++i < ft_strlen(str) && (rslt = checkhomedir(str, env, i, rslt)))
		if ((i < 2 && str[i] == '$' && str[i + 1]) || (i > 1 && str[i] == '$' &&
					str[i + 1] && str[i - 1] != '\\'))
		{
			if (str[i + 1] == '(')
			{
				if (withbracket(&i, &rslt, env, str) == 0)
					return (NULL);
			}
			else
			{
				temp2 = ft_strndup(str + i + 1, (int)ft_strlen(str + i) - 1);
				if (checkvar(getenvline(env, temp2), str, &rslt, i) == 0)
				{
					free(temp2);
					return (NULL);
				}
				i += ft_strlen(str + i);
				free(temp2);
			}
		}
	return (rslt);
}

char		*argvtest(char *str, char **env)
{
	size_t	i;
	size_t	l;
	char	*rslt;

	rslt = ft_strnew(1);
	l = 0;
	i = -1;
	return (argvtest1(str, env, rslt, i));
}
