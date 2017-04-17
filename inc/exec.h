/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:27:41 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 20:58:08 by gmorer           ###   ########.fr       */
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

int					father(t_node *tree, t_job *current_job, pid_t pid);
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
void				exec_basic_cmd(t_detail *node, char **env, int fg,
		int normal);
void				free_detail(t_detail *node);
char				*find_bin(char *arg, int error);

#endif
