/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:06:59 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/25 13:35:03 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void		alligne(int len, int size)
{
	int			i;

	i = 0;
	while ((i + size) < len)
	{
		ft_putchar(' ');
		i++;
	}
}

void			print_lst(t_info *info)
{
	int			line;
	int			column;
	t_arg		*tmp;

	line = 0;
	tmp = info->arg;
	while (line < info->line)
	{
		column = 1;
		style_print(tmp);
		alligne(info->len, (int)ft_strlen(tmp->name));
		tmp = tmp->next;
		while (tmp && tmp->start != 1 && column < info->column)
		{
			style_print(tmp);
			alligne(info->len, (int)ft_strlen(tmp->name));
			column++;
			tmp = tmp->next;
		}
		ft_putchar('\n');
		line++;
	}
}
