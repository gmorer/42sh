/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobbuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:34:46 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/05 12:28:54 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

int		ft_jobs(char **argv)
{
	t_job	*job;
	int		i;

	(void)argv;
	i = 1;
	job = shell->first_job;;
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
