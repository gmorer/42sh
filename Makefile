# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 11:35:32 by gmorer            #+#    #+#              #
#    Updated: 2017/01/11 11:16:47 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
CFLAGS = -Werror -Wextra -Wall  -g
CPATH = src/
OPATH = obj/
HPATH = include/ libft/inc
INC = $(addprefix -I , $(HPATH))
CFILES = main.c\
		 libstrstr.c\
		 get_next_line.c\
		 getbin.c\
		 builtin.c\
		 libenv.c\
		 argv.c\
		 ft_cd.c\
		 prompt.c\
		 ft_setenv.c\
		 argvtest.c\
		 ft_echo.c\
		 ft_shlvl.c\
		 ft_redirect.c\
		 ft_checklink.c\
		 hashtable.c\
		 hashtable_init.c\
		 ft_signal.c\
		 init_env.c\
		 upper.c\
		 init_shell.c\
		 jobbuiltin.c\
		 ft_fg.c\
		 glob.c\
		 glob_tree.c\
		 quote.c\
		 controller.c\
		edit_line/init_term.c \
		edit_line/prompt.c \
		edit_line/add_char.c \
		edit_line/move.c \
		edit_line/home_end.c \
		edit_line/edit_line.c \
		edit_line/up_down.c \
		edit_line/historic.c \
		edit_line/navig_hist.c \
		edit_line/misc.c \
		edit_line/manage_line.c \
		edit_line/goto.c \
		edit_line/display.c \
		edit_line/delete.c \
		edit_line/select.c \
		edit_line/copy_cut.c \
		edit_line/paste.c \
		edit_line/find_files.c \
		edit_line/completion.c \
		edit_line/create_lst.c \
		edit_line/misc_completion.c \
		edit_line/select_dir.c \
		edit_line/print_lst.c \
		edit_line/ft_select.c \
		edit_line/style_print.c \
		edit_line/comp_move.c \
		edit_line/comp_select.c \
		edit_line/put_in_str.c

OFILES = $(CFILES:.c=.o)
HFILES = include/minishell.h\
			 libft/inc/libft.h
OBJ = $(addprefix $(OPATH), $(OFILES))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -ltermcap libft/libft.a -o $(NAME)

debug: $(OBJ)
	make -C libft
	$(CC) -g  $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(OPATH)%.o: $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)edit_line
	$(CC) $(CFLAGS) $(INC) $< -c -o $@


clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
