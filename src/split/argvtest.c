/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:15:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/01 15:33:30 by gmorer           ###   ########.fr       */
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
		free(str);
		return (NULL);
	}
	return (str);
}

static char		*rm_bs(char *str)
{
	int		i;
	char	*temp3;

	i = ft_strlen(str);
	while (i >= 0 && str)
	{
		temp3 = str;
		if (str[i] == '"' && (is_reachable(str, i) || (g_shell->quote[1] &&
						(i > 0 ? str[i - 1] != '\\' : 1))))
			(temp3 = ft_strdup(rmno(str, i))) ? free(str) : 0;
		else if (str[i] == '\'' && (is_reachable(str, i) || g_shell->quote[0]))
			(temp3 = ft_strdup(rmno(str, i))) ? free(str) : 0;
		else if (str[i] == '$' && is_reachable(str, i))
			(temp3 = env_var(str, i)) ? free(str) : 0;
		else if (str[i] == '\\' && is_reachable(str, i))
			(temp3 = ft_strdup(rmno(str, i))) ? free(str) : 0;
		str = temp3;
		i--;
	}
	return (str);
}

char			*argvtest(char *str)
{
	char	*res;

	res = rm_bs(str);
	return (res);
}
