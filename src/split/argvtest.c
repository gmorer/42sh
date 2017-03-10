/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:15:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/01 16:29:09 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "env.h"
#include "shell.h"

t_shell	*g_shell;

static char		*env_var(char *str, int i)
{
	char	*temp;
	char	*temp1;

	if ((temp = getenvline(str + i + 1)) != NULL)
	{
		temp1 = ft_strndup(str, i);
		str = ft_strjoin(temp1, temp);
		free(temp);
		free(temp1);
	}
	else
	{
		return (NULL);
	}
	return (str);
}

static char		*rm_bs(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i >= 0 && str)
	{
		if (str[i] == '"' && (is_reachable(str, i) || g_shell->quote[1]))
			rmno(str, i);
		else if (str[i] == '\'' && (is_reachable(str, i) || g_shell->quote[0]))
			rmno(str, i);
		else if (str[i] == '$' && is_reachable(str, i))
			str = env_var(str, i);
		else if (str[i] == '\\' && is_reachable(str, i))
		{
			rmno(str, i);
			i--;
		}
		i--;
	}
	return (str);
}

char			*argvtest(char *str)
{
	return (ft_strdup(rm_bs(str)));
}
