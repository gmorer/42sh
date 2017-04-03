/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:57:25 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/23 15:34:49 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"

t_shell		*g_shell;

int	ft_hashtab(char **argv)
{
	int			i;
	t_binary	*bin;

	(void)argv;
	if (!g_shell->table)
		return (0);
	i = 0;
	while (i < TABLE_LEN)
	{
		if ((g_shell->table[i]) && (g_shell->table[i]->data))
		{
			bin = g_shell->table[i];
			while ((bin) && (bin->data))
			{
				ft_putnbr(i);
				ft_putstr("----------");
				ft_putstr(bin->data->name);
				ft_putstr("----------");
				ft_putendl(bin->data->full_path);
				bin = bin->next;
			}
		}
		i++;
	}
	return (0);
}
