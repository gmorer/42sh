/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobbuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:34:46 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/08 10:13:54 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"

t_shell		*g_shell;

int		ft_jobs(char **argv)
{
	t_job	*job;
	int		i;

	(void)argv;
	i = 1;
	job = g_shell->first_job;
	while (job)
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putchar(']');
		ft_putstr("		+		");
		ft_putnbr(job->pgid);
		ft_putstr("	");
		ft_putendl(job->command);
		i++;
		job = job->next;
	}
	return (0);
}
