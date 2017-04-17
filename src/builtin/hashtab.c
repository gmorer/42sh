/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:10:49 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:10:50 by rvievill         ###   ########.fr       */
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
