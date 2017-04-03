/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 12:25:01 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/25 16:43:17 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_LINE_H
# define EDIT_LINE_H

# include <termios.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# include <stdio.h>

# define BUFF *(int *)buff
# define YELLOW  "\033[3;33m"
# define RED "\033[3;31m"
# define GREEN "\033[3;32m"
# define DFL "\033[3;0m"

typedef struct			s_arg
{
	int					start;
	char				*name;
	int					selected;
	int					current;
	struct s_arg		*next;
	struct s_arg		*prev;
}						t_arg;

typedef struct			s_info
{
	t_arg				*arg;
	size_t				len_arg;
	char				*dir;
	int					fd;
	int					enter;
	int					line;
	int					column;
	int					len;
	int					nb_param;
	int					size;
}						t_info;

typedef struct			s_hist
{
	char				*cmd;
	struct s_hist		*next;
	struct s_hist		*prev;
}						t_hist;

typedef struct			s_cursor
{
	char				*line;
	char				*str_cpy;
	int					quoting;
	struct termios		term;
	int					buff_size;
	int					l_marge;
	int					r_marge;
	int					cur_col;
	int					max_col;
	int					cur_line;
	int					nb_line;
	int					beg_select;
	int					end_select;
}						t_cursor;

typedef struct			s_key
{
	int					key;
	void				(*f)(t_cursor *, t_hist **);
}						t_key;

typedef struct			s_key_selct
{
	int					key;
	void				(*f)(t_info *);
}						t_key_select;

enum					e_key
{
	PAGEUP = 2117425947,
	PAGEDO = 2117491483,
	UP = 4283163,
	DOWN = 4348699,
	LEFT = 4479771,
	RIGHT = 4414235,
	ENTER = 10,
	DELETE = 2117294875,
	BACKSPACE = 127,
	HOME = 4741915,
	END = 4610843,
	CTRL_L = 12,
	TAB = 9,
	SHIFT_L = 17458,
	SHIFT_R = 17202,
	ALT_L = 1146821403,
	ALT_R = 1130044187,
	ALT_C = 42947,
	ALT_V = 10127586,
	ALT_X = 8948194,
	OPT_UP = 1096489755,
	OPT_DOWN = 1113266971,
	SPACE = 32
}						;

/*
** historic.c
*/
void					create_hist(t_hist **hist, char **line);
/*
** edit_line.c
*/
int						edit_line(char **line, t_hist **hist, int i);
/*
** init_term.c
*/
int						init_term(t_cursor **cursor);
int						term_dfl(t_cursor *cur);
/*
** prompt.c
*/
void					prompt(void);
/*
** manage_line.c
*/
void					extend_str(t_cursor *cur);
void					move_str(char **line, int i, int way, int max);
/*
** misc.c
*/
int						my_putchar(int c);
void					set_marge(t_cursor *cursor);
void					set_pos(t_cursor *cursor, int i, int *line, int *col);
/*
** goto.c
*/
void					go_pos(t_cursor *cursor, int line, int col);
void					go_home(t_cursor *cursor);
/*
** home_end.c
*/
void					home(t_cursor *cursor, t_hist **hist);
void					end(t_cursor *cursor, t_hist **hist);
/*
** move.c
*/
void					right(t_cursor *cursor, t_hist **hist);
void					left(t_cursor *cursor, t_hist **hist);
void					next_word(t_cursor *cursor, t_hist **hist);
void					prev_word(t_cursor *cursor, t_hist **hist);
/*
** add_char.c
*/
void					add_char(char buff[5], t_cursor *cursor);
/*
** up_down.c
*/
void					up(t_cursor *cursor, t_hist **hist);
void					down(t_cursor *cursor, t_hist **hist);
/*
** display.c
*/
void					putstr_cmd(t_cursor *curs, int i);
/*
** delete.c
*/
void					backspace(t_cursor *cursor, t_hist **hist);
void					ft_delete(t_cursor *cursor, t_hist **hist);
/*
** select.c
*/
void					check_select(t_cursor *cursor, char buff[5]);
void					select_left(t_cursor *cursor, t_hist **hist);
void					select_right(t_cursor *cursor, t_hist **hist);
/*
** copy_cut.c
*/
void					copy(t_cursor *cur, t_hist **hsit);
void					cut(t_cursor *cursor, t_hist **hsit);
/*
** paste.c
*/
void					paste(t_cursor *cursor, t_hist **hist);
/*
** navig_hist.c
*/
void					up_hist(t_cursor *cursor, t_hist **hist);
void					down_hist(t_cursor *cursor, t_hist **hist);
/*
** clear.c
*/
void					ft_clear(t_cursor *cursor, t_hist **hist);
/*
** completion.c
*/
void					completion(t_cursor *cursor, t_hist **hist);
/*
** find_files.c
*/
char					**find_files(t_cursor *cursor, t_info *info, int i);
/*
** create_lst.c
*/
void					create_lst(char *av, t_info *info);
/*
** misc_completion.c
*/
int						lstlen(t_arg *arg);
void					fill_info_size(t_info *info, int ac);
void					stoc(t_info *info);
void					clear_line(t_cursor *cur, int start, int end, int col);
/*
** select_dir.c
*/
void					select_dir(t_info *info);
/*
** print_lst.c
*/
void					print_lst(t_info *info);
/*
** ft_select.c
*/
void					ft_select(t_info *info, t_cursor *cur);
/*
** style_print.c
*/
void					style_print(t_arg *arg);
/*
** comp_move.c
*/
void					s_up(t_info *info);
void					s_down(t_info *info);
void					s_left(t_info *info);
void					s_right(t_info *info);
/*
** action_select.c
*/
void					space(t_info *info);
/*
** put_in_str.c
*/
void					put_in_str(t_cursor *cur, t_info *info);

/*
** free_arg_list.c
*/
void					free_arg_list(t_arg *cur);

#endif
