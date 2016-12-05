/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:01:46 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/30 12:30:06 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_job_info (t_job *j, const char *status)
{
	fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}

t_job	*find_job(pid_t pgid, t_job *joblist)
{
	t_job *j;

	j = joblist;;
	while(j)
	{
		if (j->pgid == pgid)
			return (j);
		j = j->next;
	}
	return NULL;
}

int		job_is_stopped(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		if (!p->completed && !p->stopped)
			return (0);
		p = p->next;
	}
	return (1);
}

int		job_is_completed(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while(p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}

int		mark_process_status (pid_t pid, int status, t_shell *shell)
{
	t_job *j;
	t_process *p;

	if (pid > 0)
	{
		j = shell->first_job;///////////////
		/* Update the record for the process.  */
		while (j)
		{
			p = j->first_process;
			while (p)
			{
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED(status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED(status))
						{
							ft_putnbr((int)pid);
							ft_putstr(": Terminated by signal ");
							ft_putnbr(WTERMSIG(p->status));
							ft_putchar('\n');
							//fprintf (stderr, "%d: Terminated by signal %d.\n",(int) pid, WTERMSIG (p->status));
						}
					}
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
		ft_putendl("No child process ");
		ft_putnbr(pid);
		ft_putendl(".");
		//fprintf (stderr, "No child process %d.\n", pid);
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		/* No processes ready to report.  */
		return (-1);
	else {
		/* Other weird errors.  */
		ft_putendl_fd("waitpid", STDERR_FILENO);
		return (-1);
	}
}

void	update_status(t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status(pid, status, shell))
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

void	wait_for_job (t_job *j, t_shell *shell)
{
	int		status;
	pid_t	pid;

	pid = waitpid (WAIT_ANY, &status, WUNTRACED);
	while (!mark_process_status(pid, status, shell) && !job_is_stopped(j)
			&& !job_is_completed(j))
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
}

void	put_job_in_background (t_job *j, int cont)
{
	/* Send the job a continue signal, if necessary.  */
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putendl_fd("kill (SIGCONT)", STDERR_FILENO);
}

void	put_job_in_foreground(t_job *j, int cont, t_shell *shell)
{
	/* Put the job into the foreground.  */
	tcsetpgrp(shell->terminal, j->pgid);
	/* Send the job a continue signal, if necessary.  */
	if (cont)
	{
		tcsetattr(shell->terminal, TCSADRAIN, &j->tmodes);
		if (kill(- j->pgid, SIGCONT) < 0)
			ft_putendl_fd("kill (SIGCONT)", STDERR_FILENO);
	}
	/* Wait for it to report.  */
	wait_for_job(j, shell);
	/* Put the shell back in the foreground.  */
	tcsetpgrp(shell->terminal, shell->pgid);
	/* Restore the shell’s terminal modes.  */
	tcgetattr(shell->terminal, &j->tmodes);
	tcsetattr(shell->terminal, TCSADRAIN, &(shell->tmodes));
}


void	launch_process(t_process *p, pid_t pgid, int infile, int outfile, int errfile,
		int foreground, t_shell *shell)
{
	pid_t pid;

	if (shell->is_interactive)
	{
		pid = getpid ();
		if (pgid == 0) pgid = pid;
		setpgid (pid, pgid);
		if (foreground)
			tcsetpgrp (STDIN_FILENO, pgid);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	if (infile != STDIN_FILENO)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile != STDOUT_FILENO)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	if (errfile != STDERR_FILENO)
	{
		dup2(errfile, STDERR_FILENO);
		close(errfile);
	}
	execvp(p->argv[0], p->argv);
	ft_putendl_fd("execvp", STDERR_FILENO);
	exit (1);
}

void	launch_job(t_job *j, int foreground, t_shell *shell)
{
	t_process	*p;
	pid_t	pid;
	int		mypipe[2];
	int		infile;
	int		outfile;

	infile = j->stdin;
	p = j->first_process;
	while (p)
	{
		if (p->next)
		{
			if (pipe(mypipe) < 0)
			{
				ft_putendl_fd("pipe", STDERR_FILENO);
				exit (1);
			}
			outfile = mypipe[1];
		}
		else
			outfile = j->stdout;
		pid = fork();
		if (pid == 0)
			launch_process(p, j->pgid, infile, outfile, j->stderr, foreground, shell);
		else if (pid < 0)
		{
			ft_putendl_fd("fork", STDERR_FILENO);
			exit (1);
		}
		else
		{
			p->pid = pid;
			if (shell->is_interactive)
			{
				if (!j->pgid)
					j->pgid = pid;
				setpgid(pid, j->pgid);
			}
		}
		/* Clean up after pipes.  */
		if (infile != j->stdin)
			close (infile);
		if (outfile != j->stdout)
			close (outfile);
		infile = mypipe[0];
		p = p->next;
	}
	format_job_info(j, "launched");
	if (!shell->is_interactive)
		wait_for_job(j, shell);
	else if (foreground)
		put_job_in_foreground(j, 0, shell);
	else
		put_job_in_background(j, 0);
}

void	free_job(t_job *job)
{
	free(job->command);
	//free all process
	free(job);
}

void	do_job_notification(t_shell *shell)
{
	t_job		*j;
	t_job		*jlast;
	t_job		*jnext;

	/* Update status information for child processes.  */
	update_status(shell);
	j = shell->first_job;///////////////////////
	jlast = NULL;
	while (j)
	{
		jnext = j->next;

		/* If all processes have completed, tell the user the job has
		 *          completed and delete it from the list of active jobs.  */
		if (job_is_completed(j)) {
			format_job_info(j, "completed");
			if (jlast)
				jlast->next = jnext;
			else
				shell->first_job = jnext;
			free_job(j);
		}

		/* Notify the user about stopped jobs,
		 *          marking them so that we won’t do this more than once.  */
		else if (job_is_stopped(j) && !j->notified) {
			format_job_info(j, "stopped");
			j->notified = 1;
			jlast = j;
		}

		/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
		j = jnext;
	}
}

void	mark_job_as_running (t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
	j->notified = 0;
}

void	continue_job(t_job *j, int foreground, t_shell *shell)
{
	mark_job_as_running(j);
	if (foreground)
		put_job_in_foreground(j, 1, shell);
	else
		put_job_in_background(j, 1);
}
