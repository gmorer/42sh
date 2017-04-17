/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobbuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 09:48:24 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/06 09:48:29 by rvievill         ###   ########.fr       */
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
