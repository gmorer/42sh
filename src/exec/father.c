/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:19:23 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/14 17:25:02 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int			father(t_node *tree, t_job *current_job, pid_t pid)
{
	int status;

	status = 0;
	dup2(tree->in, STDIN_FILENO);
	dup2(tree->out, STDOUT_FILENO);
	dup2(tree->err, STDERR_FILENO);
	current_job->pgid = pid;
	setpgid(pid, pid);
	if (tree->fg)
		status = wait_for_job(current_job);
	else
	{
		ft_putchar('[');
		ft_putnbr(add_job(current_job));
		ft_putstr("]	");
		ft_putnbr(current_job->pgid);
		ft_putchar('\n');
	}
	return (status);
}
