/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_par_ast.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:27:55 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 17:58:41 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_PAR_AST_H
# define LEX_PAR_AST_H

# include "../libft/libft.h"
# include <stdio.h>

/*
** Structure de la sous-liste de commande
** (comprend tout ce qui est situe entre 2 separateurs)
*/
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

/*
** Structure temporaire du lexer/parser
*/
typedef struct		s_lex
{
	char			*space;
	char			*str;
	int				placed;
	t_detail		*lst;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

/*
** Structure de l'AST
*/
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

/*
** Types de redirections
*/
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
t_lex				*lexer(char **line, char *cursor, int i);
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
void				advance_pos(char **line, int length);
int					is_sep(char *str);
int					check_nbr(char *str);

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
char				*cur_lex_str(t_lex *lst);

/*
** CHECK_REDIR.C
*/
t_detail			*check_redir(t_detail *cursor);

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
t_detail			*redir_pars_error(t_detail *cursor, int type);

#endif
