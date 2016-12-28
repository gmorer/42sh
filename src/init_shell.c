/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:29:11 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/23 17:04:47 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

t_shell		*init_mainprocess(void)
{
	if (!(shell = (t_shell*)malloc(sizeof(t_shell))))
		return (NULL);
	shell->terminal = STDIN_FILENO;
	shell->is_interactive = isatty (shell->terminal);
	if (!shell->is_interactive)
	{
		ft_putendl_fd("shell isnt interactiv!", STDERR_FILENO);
		return(NULL);
	}
	shell->first_job = NULL;
	/* Loop until we are in the foreground.  */
	while (tcgetpgrp (shell->terminal) != (shell->pgid = getpgrp ()))
		kill (- shell->pgid, SIGTTIN);
	/* Put ourselves in our own process group.  */
	shell->pgid = getpid ();
	if (setpgid (shell->pgid, shell->pgid) < 0)
	{
		ft_putendl_fd("Couldn't put the shell in its own process group", STDERR_FILENO);
		exit (1);
	}
	/* Grab control of the terminal.  */
	tcsetpgrp (shell->terminal, shell->pgid);
	shell->hist = NULL;
	/* Save default terminal attributes for shell.  */
	tcgetattr (shell->terminal, &(shell->tmodes));
	ft_putendl("initializing success");
	return (shell);
}
