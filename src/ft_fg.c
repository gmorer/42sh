/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 12:15:36 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/06 15:56:56 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		 *shell;

int			ft_fg(char **argv)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	(void)argv;
	ft_putnbr(shell->first_job->pgid);
	tcsetpgrp(shell->terminal, shell->first_job->pgid);
	//if (kill(-shell->first_job->pgid, SIGCONT) < 0)
	//	perror("kill error");
	pid = waitpid(WAIT_ANY, &status, WUNTRACED);
	ft_signal();
	return (0);
}
