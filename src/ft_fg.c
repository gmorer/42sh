/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/06 17:45:57 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		 *shell;

t_job		*find_job_name(char *str)
{
	t_job	*job;
	t_job	*temp;
	int		find;

	find = 0;
	job = NULL;
	temp = shell->first_job;
	while (temp)
	{
		if (ft_strcmp(temp->name, str) == 0)
		{
			job = temp;
			find++;
		}

		temp = temp->next;
	}
	if (find > 1)
		ft_triplestr("42sh: fg: ", str, ": ambiguous job spec\n");
	if (find == 0)
		ft_triplestr("42sh: fg: ", str, ": no such job\n");
	if (find == 1)
		return (job);
	else
		return (NULL);
}

int			ft_fg(char **argv)
{
	t_job	*job;


	job = shell->first_job;
	if (!job)
	{
		ft_putendl("fg: no currentjob");
		return (1);
	}
	if (argv[1] == NULL)
	{
		while (job->next)
			job = job->next;
	}
	if (kill(- job->pgid, SIGCONT) < 0)
		perror("kill error");
	tcsetpgrp(shell->terminal, job->pgid);
	wait_for_job(job);
	tcsetpgrp(shell->terminal, shell->pgid);
	tcsetattr(shell->terminal, TCSADRAIN, &(shell->dfl_term));
	return (0);
}
