/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_par_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:18:19 by acottier          #+#    #+#             */
/*   Updated: 2017/03/08 14:08:02 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_PAR_AST_H
# define LEX_PAR_AST_H

# include "../libft/libft.h"
# include <stdio.h>

typedef struct		s_detail
{
	char			**redir_str;
	char			**argv;
	int				pipe;
	int				*redir;
	int				*fd_file;
	int				*fd_std;
	int				pfd[2];
	struct s_detail	*next;
	struct s_detail *prev;
}					t_detail;

typedef struct		s_lex
{
	char			*str;
	int				placed;
	t_detail		*lst;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

typedef struct		s_node
{
	char			*str;
	int				ret_cmd;
	int				in;
	int				out;
	int				err;
	int				fg;
	t_detail		*lst;
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*prev;
}					t_node;

enum				e_type
{
	DB_R,
	S_R,
	S_L,
	DB_L
}					;

/*
** LEXER.C
*/
t_lex				*lexer(char *line, char *cursor, int i);
int					target(char *str, int type);
t_lex				*add_link(char *str, t_lex *prev, int add, int merge);

/*
** REDIRECTION.C
*/
int					agreg_prefix(char *line, int limit);
int					redirection(char **line, t_lex **res);

/*
** MISC_LEXER.C
*/
int					redir_in_scope(char *line, int scope);
int					quote_scope(char *line, char quote, int i);
int					next_sep(char *line);
void				advance_pos(char **line, int length);
int					is_sep(char *str);

/*
** PARSER.C
*/
t_lex				*parser(t_lex *lst);

/*
** CHAIN.C
*/
t_detail			*str_to_lst(char *str);

/*
** MISC_PARSER.C
*/
int					target(char *str, int type);
t_lex				*to_start(t_lex *lst);
t_lex				*pars_next_sep(t_lex *lex);
int					check_redir_tab(char **redir_str);

/*
** MKTREE.C
*/
t_node				*mktree(t_lex *lex);

/*
** MISC_AST.C
*/
t_lex				*get_sep_link(t_lex *lex);
t_node				*mknode_sep(t_lex *lex, t_node *prev);
t_node				*mknode_simple(t_lex *lex, t_node *prev);
void				free_tree(t_node *tree);

/*
** ERROR_MESSAGE_PARS.C
*/
t_detail			*cmd_pars_error(t_detail *cursor, int err);
t_lex				*sep_pars_error(t_lex *cursor, int err);

#endif
