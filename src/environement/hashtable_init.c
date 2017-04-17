/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:17:49 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:17:51 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "env.h"
#include "builtin.h"

static t_binary	*ft_remp(char *binary, char *path)
{
	char		*temp;
	t_binary	*bin;

	if (!(bin = malloc(sizeof(t_binary))))
		return (NULL);
	temp = NULL;
	if (!(bin->data = malloc(sizeof(t_data))))
		return (NULL);
	bin->data->name = ft_strdup(binary);
	bin->next = NULL;
	temp = ft_strjoin(path, "/");
	bin->data->full_path = ft_strjoin(temp, binary);
	ft_strdel(&temp);
	return (bin);
}

void			add_hash_to_tab(char *binary, char *path)
{
	int			result;
	t_binary	*last;

	if ((result = ft_hash_algo(binary)) == -1)
	{
		ft_putendl("Cannot add hash to table");
		return ;
	}
	if (g_shell->table[result] == NULL)
		g_shell->table[result] = ft_remp(binary, path);
	else
	{
		last = g_shell->table[result];
		while ((last->next))
			last = last->next;
		last->next = ft_remp(binary, path);
		last->next->next = NULL;
	}
	return ;
}

t_binary		**ft_init_hash_table(void)
{
	t_binary	**result;
	int			i;

	if (!(result = (t_binary**)malloc(sizeof(t_binary*) *
					((unsigned long)TABLE_LEN))))
		return (NULL);
	i = 0;
	while (i < TABLE_LEN)
	{
		result[i] = NULL;
		i++;
	}
	return (result);
}
