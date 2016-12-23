/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 17:15:52 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/23 13:27:14 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** type : 0 -> normal string
**		: 1 -> 'string'
**		: 2 -> "string"
*/

t_shell		*shell;

char		*argv_type2(char *str)
{
	char	*rslt;
	int		i;
	char	*temp;
	char	*temp1;

	i = 0;
	rslt = ft_strdup(str);
	while (rslt[i])
	{
		if (rslt[i] == '"' && (i == 0 || (i > 0 && rslt[i - 1] != '\\')))
			rslt = rmno(rslt, i);
		else if (rslt[i] == '$' && (i == 0 || (i > 0 && rslt[i - 1] != '\\'))
				&& rslt[i + 1] && rslt[i + 1] != '(')
		{
			if ((temp = getenvline(shell->env, rslt + i + 1)) != NULL)
			{
				temp1 = ft_strndup(rslt, i);
				free(rslt);
				rslt = ft_strjoin(temp1, temp);
				free(temp);
				free(temp1);
			}
			else
			{
				free(rslt);
				return (NULL);
			}
		}
		else if (rslt[i] == '$' && (i == 0 || (i > 0 && rslt[i - 1] != '\\'))
				&& rslt[i + 1] && rslt[i + 1] == '(')
		{
			;
		}
		i++;
	}
	return (rslt);
}

char		*argvtest(char *str)
{
	int	type;
	char	*result;

	type = 0;
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		type = 1;
	else if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		type = 2;
	if (type == 0)
		return (argv_type2(str));
	result = ft_strdup(str);
	result = rmno(result, ft_strlen(str) - 1);
	result = rmno(result, 0);
	if (type == 1)
		return (result);
	else if (type == 2)
		return (argv_type2(result));
	ft_putendl("error");
	return (ft_strdup(str));
}
