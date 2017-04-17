/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:26 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 14:55:59 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "env.h"
#include "shell.h"

t_shell	*g_shell;

static int		toto(char *str, int i)
{
	while (i > 0 && i--)
		if (str[i] == '\'' && str[i - 1] != '\\')
			return (0);
	return (1);
}

static char		*bel_to_space(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = str[i] == 7 ? 32 : str[i];
		i++;
	}
	return (str);
}

static char		*env_var(char *str, int i)
{
	char	*temp[2];
	char	*temp2;
	size_t	j;

	j = i;
	while (str[j] && str[j + 1] != '"' && str[j + 1] != '\'')
		j++;
	temp2 = ft_strsub(str, i + 1, j - i);
	if ((temp[0] = getenvline(temp2)) != NULL)
	{
		temp[1] = ft_strndup(str, i);
		temp[1] = ft_freejoin(temp[1], temp[0]);
		str = (j < ft_strlen(str)) ? ft_strjoin(temp[1], str + j + 1)
			: ft_strdup(temp[1]);
		ft_strdel(&temp[0]);
		ft_strdel(&temp[1]);
	}
	else
	{
		ft_strdel(&temp2);
		ft_strdel(&str);
		return (NULL);
	}
	ft_strdel(&temp2);
	return (str);
}

static char		*rm_spec_chars(char *str)
{
	int		i;
	char	*temp3;

	i = ft_strlen(str);
	while (i >= 0 && str)
	{
		temp3 = str;
		if (str[i] == '"' && (is_reachable(str, i) || (g_shell->quote[1] &&
						(i > 0 ? str[i - 1] != '\\' : 1))))
			(temp3 = ft_strdup(rmno(str, i))) ? ft_strdel(&str) : 0;
		else if (str[i] == '\'' && (is_reachable(str, i) || g_shell->quote[0]))
			(temp3 = ft_strdup(rmno(str, i))) ? ft_strdel(&str) : 0;
		else if (str[i] == '$' && toto(str, i) &&
				(i == 0 || str[i - 1] != '\\'))
			(temp3 = env_var(str, i)) ? ft_strdel(&str) : 0;
		else if (str[i] == '\\' && is_reachable(str, i) && (str[i + 1] == '"'
					|| str[i + 1] == '\\' || str[i + 1] == '$'
					|| str[i + 1] == '\'' || !g_shell->quote[1]))
			(temp3 = ft_strdup(rmno(str, i))) ? ft_strdel(&str) : 0;
		str = temp3;
		i--;
	}
	return (str);
}

char			*argvtest(char *str)
{
	char	*res;

	res = rm_spec_chars(str);
	return (bel_to_space(res));
}
