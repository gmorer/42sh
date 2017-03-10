/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 13:33:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/07 13:13:29 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"

t_shell		*g_shell;

int		free_job(void)
{
	t_job	*temp;
	t_job	*prev;

	temp = g_shell->first_job;
	while (temp)
	{
		prev = temp;
		temp = temp->next;
		if (kill(prev->pgid, 0) != -1)
			kill(prev->pgid, SIGTERM);
		if (kill(prev->pgid, 0) != -1)
			kill(prev->pgid, SIGKILL);
		free(prev->command);
		free(prev);
	}
	return (0);
}

int		ft_exit(char **argv)
{
	int i;

	if (ft_strstrlen(argv) > 2)
	{
		ft_putendl("exit: too many arguments");
		return (1);
	}
	if (ft_strstrlen(argv) == 1)
	{
		ft_free_hash_tab();
		free_job();
		tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
		exit(0);
	}
	i = ft_atoi(argv[1]);
	if (!i)
	{
		ft_putendl("exit: Expression Syntax.");
		return (1);
	}
	ft_free_hash_tab();
	free_job();
	tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
	exit(i);
}
