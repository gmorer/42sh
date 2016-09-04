/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:34:32 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/07 17:16:14 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_setenvcheck(char **argv)
{
	char	**temp1;
	char	**temp2;
	char	**temp3;

	if (ft_strstrlen(argv) != 2)
		return (ft_strstrdup(argv));
	else if (ft_strchr(argv[1], '=') == NULL)
		return (ft_strstrdup(argv));
	temp1 = ft_strstrnew(2);
	temp1[0] = ft_strdup("setenv\0");
	temp2 = ft_strsplit(argv[1], '=');
	if (ft_strstrlen(temp2) != 2)
	{
		free(temp2);
		free(temp1);
		return (ft_strstrdup(argv));
	}
	temp3 = ft_strstrjoin(temp1, temp2);
	return (temp3);
}

int			ft_setenv(char **argv, char ***env)
{
	int		i;
	char	*temp;
	char	**argvtemp;

	temp = NULL;
	argvtemp = ft_setenvcheck(argv);
	if (argvtemp[1])
		temp = ft_strjoin(argvtemp[1], "=");
	if (ft_strstrlen(argvtemp) != 3)
	{
		ft_putendl("setenv: bad usage");
		return (1);
	}
	if ((i = casenofor(*env, argvtemp[1])) == -1)
		*env = ft_strstradd(ft_strjoin(temp, argvtemp[2]), *env);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strjoin(temp, argvtemp[2]);
	}
	ft_strstrfree(argvtemp);
	free(temp);
	return (0);
}
