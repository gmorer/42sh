/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:17:41 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:17:42 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"

t_shell		*g_shell;

static t_binary		*free_bin(t_binary *bin)
{
	t_binary *bin2;

	bin2 = bin;
	bin = bin->next;
	ft_strdel(&bin2->data->name);
	ft_strdel(&bin2->data->full_path);
	free(bin2->data);
	free(bin2);
	return (bin);
}

int					ft_hash_algo(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		result = str[i++] + result * 10;
	}
	result = result % TABLE_LEN;
	return (ft_abs(result));
}

int					ft_free_hash_tab(void)
{
	int			i;
	t_binary	*bin;
	t_binary	*bin2;

	if (!(i = 0) && !g_shell->table)
		return (0);
	while (i < TABLE_LEN)
	{
		bin = g_shell->table[i];
		if ((bin))
		{
			bin2 = bin;
			if (bin->data)
				while ((bin))
				{
					bin = free_bin(bin);
				}
			else
				free(bin);
		}
		i++;
	}
	free(g_shell->table);
	g_shell->table = NULL;
	return (0);
}
