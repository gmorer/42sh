# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/05 12:45:55 by rvievill          #+#    #+#              #
#    Updated: 2017/03/09 15:54:08 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
NAME= 21sh
CFLAGS= -g -Wall -Werror -Wextra -fsanitize=address
CPATH= src/
OPATH= obj/
HPATH= inc/ libft/
INC= $(addprefix -I, $(HPATH))
CFILES= main.c \
		get_next_line.c \
		edit_line/add_char.c \
		edit_line/comp_move.c \
		edit_line/comp_select.c \
		edit_line/completion.c \
		edit_line/copy_cut.c \
		edit_line/create_lst.c \
		edit_line/delete.c \
		edit_line/display.c \
		edit_line/edit_line.c \
		edit_line/find_files.c \
		edit_line/ft_select.c \
		edit_line/goto.c \
		edit_line/historic.c \
		edit_line/home_end.c \
		edit_line/init_term.c \
		edit_line/manage_line.c \
		edit_line/misc.c \
		edit_line/misc_completion.c \
		edit_line/move.c \
		edit_line/navig_hist.c \
		edit_line/paste.c \
		edit_line/print_lst.c \
		edit_line/prompt.c \
		edit_line/put_in_str.c \
		edit_line/select.c \
		edit_line/select_dir.c \
		edit_line/style_print.c \
		edit_line/up_down.c \
		lex_par_ast/lexer.c \
		lex_par_ast/misc_ast.c \
		lex_par_ast/misc_lexer.c \
		lex_par_ast/mktree.c \
		lex_par_ast/parser.c \
		lex_par_ast/chain.c \
		lex_par_ast/misc_parser.c \
		lex_par_ast/redirection.c \
		lex_par_ast/error_message_pars.c \
		split/argv.c \
		split/argvtest.c \
		split/glob.c \
		split/glob_tree.c \
		split/quote.c \
		split/bracket.c \
		environement/libenv.c \
		environement/hashtable.c \
		environement/hashtable_init.c \
		environement/init_shell.c \
		environement/init_env.c \
		environement/ft_shlvl.c \
		exec/controller.c \
		exec/exec_cmd.c \
		exec/linkio.c \
		exec/find_bin.c \
		exec/error_message.c \
		exec/redir.c \
		exec/heredoc_assign.c \
		exec/exec_check.c \
		exec/walkthrough.c \
		exec/free_detail.c \
		builtin/ft_cd.c \
		builtin/ft_echo.c \
		builtin/exit.c \
		builtin/find_builtin.c \
		builtin/ft_fg.c \
		builtin/ft_setenv.c \
		builtin/hashtab.c \
		builtin/unsetenv.c \
		builtin/jobbuiltin.c \
		builtin/ft_env.c \
		builtin/env_opt.c

OFILES= $(CFILES:.c=.o)

HFILES= inc/edit_line.h \
		inc/lex_par_ast.h \
		inc/split.h \
		inc/env.h \
		inc/exec.h \
		inc/hashtab.h \
		inc/shell.h \
		libft/libft.h

OBJ= $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean name re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)/edit_line
	@mkdir -p $(OPATH)/lex_par_ast
	@mkdir -p $(OPATH)/split
	@mkdir -p $(OPATH)/exec
	@mkdir -p $(OPATH)/environement
	@mkdir -p $(OPATH)/builtin
	$(CC) -g -Wall -Werror -Wextra  $(INC) $< -c -o $@

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
