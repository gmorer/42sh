/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 12:28:52 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/05 13:25:47 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

static void			underline(char *arg)
{
	ft_putstr("\033[4;37m");
	ft_putstr(arg);
	ft_putstr("\033[0m");
}

static void			highlight(char *arg)
{
	ft_putstr("\033[7;37m");
	ft_putstr(arg);
	ft_putstr("\033[0m");
}

static void			underline_highlight(char *arg)
{
	ft_putstr("\033[7;4;37m");
	ft_putstr(arg);
	ft_putstr("\033[0m");
}

void				style_print(t_arg *arg)
{
	if (arg->name)
	{
		if (arg->selected == 1 && arg->current == 0)
			highlight(arg->name);
		else if (arg->selected == 0 && arg->current == 1)
			underline(arg->name);
		else if (arg->selected == 1 && arg->current == 1)
			underline_highlight(arg->name);
		else
			ft_putstr(arg->name);
	}
}
