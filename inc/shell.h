/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:30:59 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/07 12:54:16 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <signal.h>
# include "exec.h"
# include "edit_line.h"
# include "hashtab.h"

typedef struct		s_shell
{
	struct termios	cur_term;
	struct termios	dfl_term;
	t_job			*first_job;
	t_cursor		*cursor;
	pid_t			pgid;
	char			**env;
	char			*av;
	int				quote[2];
	t_hist			*hist;
	t_binary		**table;
}					t_shell;

extern t_shell		*g_shell;

t_shell				*init_mainprocess(void);
char				*toexec(char *argv);

#endif
