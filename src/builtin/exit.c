/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:09:51 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 20:58:52 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

t_shell		*g_shell;

int		ft_exit(char **argv)
{
	int i;

	if (ft_strstrlen(argv) > 2)
		ft_putendl("exit: too many arguments");
	if (ft_strstrlen(argv) > 2)
		return (1);
	tcsetpgrp(1, getppid());
	if (ft_strstrlen(argv) == 1)
	{
		ft_free_hash_tab();
		tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
		if (g_shell)
			free_shell(&g_shell);
		exit(0);
	}
	if (!(i = ft_atoi(argv[1])))
	{
		ft_putendl("exit: Expression Syntax.");
		return (1);
	}
	ft_free_hash_tab();
	tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
	if (g_shell)
		free_shell(&g_shell);
	exit(i);
}
