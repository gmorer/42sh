/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:11:12 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:11:14 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

t_shell		*g_shell;

int		ft_unsetenv(char **argv)
{
	int		i;

	if (ft_strstrlen(argv) != 2)
	{
		ft_putstr("unsetenv: bad usage\nusage: ");
		ft_putendl("unsetenv [environement varibale]");
		return (1);
	}
	if ((i = casenofor(argv[1])) == -1)
	{
		ft_putstr("unsetenv: no variable ");
		ft_putstr(argv[1]);
		ft_putendl(" in the environement");
		return (1);
	}
	if (ft_strcmp(argv[1], "BINARY_LEN") == 0)
		return (0);
	if (ft_strcmp(argv[1], "PATH") == 0)
		ft_free_hash_tab();
	g_shell->env = ft_strstrdelone(i, g_shell->env);
	return (0);
}
