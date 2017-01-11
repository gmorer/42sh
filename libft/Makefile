# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmorer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/01 11:36:51 by gmorer            #+#    #+#              #
#    Updated: 2017/01/11 11:27:27 by gmorer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS= -Weverything
CPATH = src/
HPATH = inc/
OPATH = obj/
CFILES =	ft_abs.c\
			ft_strequ.c\
			ft_strnequ.c\
			ft_atoi.c\
			ft_bzero.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isprint.c\
			ft_isspace.c\
			ft_isfolder.c\
			ft_itoa.c\
			ft_memalloc.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memdel.c\
			ft_memmove.c\
			ft_memset.c\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putendl.c\
			ft_putendl_fd.c\
			ft_putnbr.c\
			ft_putnbr_fd.c\
			ft_putstr.c\
			ft_putstr_fd.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strclr.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strndup.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlen.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strncat.c\
			ft_strncmp.c\
			ft_strncpy.c\
			ft_strnew.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strsplit.c\
			ft_strstr.c\
			ft_strsub.c\
			ft_strtrim.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_strswitch.c\
			ft_strrev.c\
			ft_putmap.c\
			ft_pow.c\
			ft_lstnew.c\
			ft_lstmap.c\
			ft_lstiter.c\
			ft_lstdelone.c\
			ft_lstdel.c\
			ft_lstadd.c\
			ft_strisdigit.c\
			ft_triplestr.c\
			ft_swap.c

HFILES = inc/libft.h
INC = $(addprefix -I , $(HPATH))
OBJ = $(addprefix $(OPATH), $(CFILES:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OPATH)%.o : $(CPATH)%.c $(HFILES)
	@mkdir -p $(OPATH)
	$(CC) $(INC) $< -c -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
