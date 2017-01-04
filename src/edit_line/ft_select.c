/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 11:55:53 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/03 10:26:34 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"

int						action_select(t_info *info, char buff[5])
{
	int					i;
	//const t_key_select	key[5] = {
	//	{LEFT, &s_left}, {RIGHT, &s_right}, {SPACE, &space}};
	const t_key_select	key[6] = {
		{LEFT, &s_left}, {RIGHT, &s_right}, {SPACE, &space}, {TAB, &s_right}};

	i = 0;
	while (i < 6)
	{
		if (BUFF == key[i].key)
		{
			key[i].f(info);
			return (0);
		}
		i++;
	}
	return (1);
}

static int				key(t_info *info)
{
	char				buff[5];

	*(int *)buff = 0;
	read(0, buff, 4);
	if (action_select(info, buff) == 1)
		return (1);
	if (*(int *)buff == ENTER)
	{
		info->enter = 1;
		return (1);
	}
	return (0);
}

void					ft_select(t_info *info, t_cursor *cur)
{
	int					line;
	int					col;

	col = cur->cur_col;
	line = cur->cur_line;
	if (lstlen(info->arg) > 0)
	{
		tputs(tgetstr("vi", 0), 1, my_putchar);
		while (1)
		{
			go_pos(cur, line + 1, 0);
			cur->cur_line += info->line;
			print_lst(info);
			if (key(info) == 1)
				break ;
		}
		clear_line(cur, line + 1, info->line + line + 1, 0);
		tputs(tgetstr("ve", 0), 1, my_putchar);
		go_pos(cur, line, col);
	}
	else
		info->arg->selected = 1;
	put_in_str(cur, info);
}
