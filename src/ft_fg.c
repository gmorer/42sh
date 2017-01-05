/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/05 15:26:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		 *shell;

int			ft_fg(char **argv)
{
	//int		status;
	char	**temp;
	t_job	*job;


	temp = NULL;
	(void)argv;
	job = shell->first_job;
	if (!job)
	{
		ft_putendl("fg: no currentjob");
		return (1);
	}
	while (job->next)
		job = job->next;
	ft_putstr("relaunch de : ");
	ft_putnbr(job->pgid);
	ft_putchar('\n');
	if (kill(- job->pgid, SIGCONT) < 0)
		perror("kill error");
	if (tcsetpgrp(shell->terminal, job->pgid) == -1)
	{
		ft_putendl("error fg");
		if (errno == EBADF)
			ft_putendl("fd n'est pas un descripteur valide.");
		if (errno == EINVAL)
			ft_putendl("pgrp a une valeur illégale.");
		if (errno == ENOTTY)
			ft_putendl("Le processus appelant n'a pas de terminal de contrôle, ou il en a un mais ce n'est pas celui décrit par fd, ou, pour tcsetpgrp(), ce terminal de contrôle n'est plus associé avec la session du processus appelant.");
		if (errno == EPERM)
			ft_putendl("pgrp a une valeur légale, mais ce n'est pas l'ID d'un groupe de processus dans la même session que le processus appelant.");
		perror("tcsetpgrp");
	}
	wait_for_job(job);
	//waitpid(WAIT_ANY, &status, WUNTRACED);
	tcsetpgrp(shell->terminal, shell->pgid);
	tcsetattr(shell->terminal, TCSADRAIN, &(shell->dfl_term));
	ft_signal();
	boucle(temp, 0, shell->table);
	return (0);
}
