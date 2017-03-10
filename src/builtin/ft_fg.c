/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/09 15:21:08 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"

t_shell				*g_shell;

static t_job		*find_job_by_id(char *str, int *find)
{
	t_job		*job;
	int			id;
	int			i;

	*find = 1;
	i = 1;
	job = g_shell->first_job;
	id = ft_atoi(str);
	while (job)
	{
		if (i == id)
			return (job);
		i++;
		job = job->next;
	}
	return (NULL);
}

static t_job		*find_job_by_name(char *str, int *find)
{
	t_job	*job;
	t_job	*temp;

	job = NULL;
	temp = g_shell->first_job;
	while (temp)
	{
		if (ft_strcmpset(temp->command, str) == 0)
		{
			job = temp;
			(*find)++;
		}
		temp = temp->next;
	}
	return (job);
}

static t_job		*find_job_fg(char *str)
{
	t_job	*job;
	int		find;

	find = 0;
	if (str && str[0] == '%')
		str++;
	if (ft_strisdigit(str))
		job = find_job_by_id(str, &find);
	else
		job = find_job_by_name(str, &find);
	if (find > 1)
		ft_triplestr("42sh: fg: ", str, ": ambiguous job spec\n");
	if (find == 0 || job == NULL)
		ft_triplestr("42sh: fg: ", str, ": no such job\n");
	if (find == 1)
		return (job);
	else
		return (NULL);
}

int					ft_bg(char **argv)
{
	t_job	*job;

	job_quit(9);
	job = g_shell->first_job;
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
	else
		job = find_job_fg(argv[1]);
	if (!job)
		return (1);
	if (kill(-job->pgid, SIGCONT) < 0)
		perror("kill error");
	return (0);
}

int					ft_fg(char **argv)
{
	t_job	*job;

	job_quit(9);
	job = g_shell->first_job;
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
	else
		job = find_job_fg(argv[1]);
	if (!job)
		return (1);
	if (kill(-job->pgid, SIGCONT) < 0)
		perror("kill error");
	tcsetpgrp(1, job->pgid);
	wait_for_job(job);
	tcsetpgrp(1, g_shell->pgid);
	tcsetattr(1, TCSADRAIN, &(g_shell->dfl_term));
	return (0);
}
