/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:26:05 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/17 12:01:14 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "env.h"
#include "shell.h"

t_shell		*g_shell;

/*
** return 0 if special char is disable by " or ' or \
*/

int		is_reachable(char *str, int i)
{
	g_shell->quote[0] = 0;
	g_shell->quote[1] = 0;
	if (i == 0)
		return (1);
	if (str[i - 1] == '\\' && is_reachable(str, i - 1))
		return (0);
	if (str[i] == '?' && (i > 0 || (str[i - 1] == '$' && str[i - 1])))
		return (0);
	if (!is_not_quote(str, i) && (g_shell->quote[0] ? 1 : (str[i] != '\\')))
	{
		if (g_shell->quote[0] && str[i] == '\'')
			return (1);
		if (g_shell->quote[1] && str[i] == '"')
			if ((str[i - 1] == '\\' && !is_reachable(str, i - 1)) ||
					str[i - 1] != '\\')
				return (1);
		return (0);
	}
	return (1);
}

char	*ft_quote_add(char *av)
{
	char	*result;
	char	*buff;
	char	*tmp;

	tmp = NULL;
	if (!av)
		av = g_shell->av;
	if (g_shell->quote[0])
		ft_putstr("'> ");
	else if (g_shell->quote[1])
		ft_putstr("\"> ");
	else
		ft_putstr("\\> ");
	if (edit_line(&buff, &(g_shell->hist), 0) == -1)
		if (get_next_line(0, &buff) == 0)
			return (ft_strdup(av));
	tmp = ft_strjoin("\n", buff);
	buff ? free(buff) : NULL;
	result = ft_strjoin(av, tmp);
	g_shell->av = result;
	free(tmp);
	return (result);
}

char	*ft_quote(char *av)
{
	int		i;
	char	*temp;

	if (!av)
		return (NULL);
	i = ft_strlen(av);
	if (is_reachable(av, i))
		return (av);
	g_shell->av = av;
	g_shell->quote[0] = 0;
	g_shell->quote[1] = 0;
	while ((i = ft_strlen(av)) && !is_reachable(av, i))
	{
		temp = ft_quote_add(av);
		av ? free(av) : NULL;
		av = temp;
	}
	return (av);
}
