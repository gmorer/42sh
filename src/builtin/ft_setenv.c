/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:34:32 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/09 11:14:42 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "hashtab.h"
#include "shell.h"

t_shell		*g_shell;

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

int			ft_setenv(char **argv)
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
		ft_strstrfree(argvtemp);
		return (1);
	}
	if ((i = casenofor(argvtemp[1])) == -1)
		g_shell->env = ft_strstradd(ft_strjoin(temp, argvtemp[2]), g_shell->env);
	else
	{
		if (g_shell->table && ft_strcmp(temp, "BINARY_LEN=") == 0)
		{
			ft_strstrfree(argvtemp);
			free(temp);
			return (0);
		}
		free(g_shell->env[i]);
		g_shell->env[i] = ft_strjoin(temp, argvtemp[2]);
	}
	if (ft_strcmp(temp, "PATH=") == 0)
	{
		ft_free_hash_tab();
		g_shell->table = ft_init_hash_table();
		ft_strstrfree(argvtemp);
		free(temp);
		return (0);
	}
	ft_strstrfree(argvtemp);
	free(temp);
	return (0);
}
