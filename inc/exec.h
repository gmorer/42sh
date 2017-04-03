/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:32:26 by gmorer            #+#    #+#             */
/*   Updated: 2017/04/03 18:30:01 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include "lex_par_ast.h"

typedef struct		s_job
{
	struct s_job	*next;
	char			*command;
	pid_t			pgid;
}					t_job;

void				job_quit(int sig);
int					delet_job(t_job *job);
int					add_job(t_job *job);
int					wait_for_job(t_job *job);
int					ft_strcmpset(char *str1, char *str2);
int					prep_exec(t_node *tree, char **env);
char				*error_message(int ret, char *cmd);
t_node				*walkthrough(t_node *tree);
int					select_redir(t_node *tree);
char				*get_file(char *str);
int					linkio(t_detail *node);
void				heredoc_assign(t_node *tree);
int					heredoc(t_detail *node, int type, char *end, int i);
void				exec_basic_cmd(t_detail *node, char **env, int fg);
void				free_detail(t_detail *node);

#endif
