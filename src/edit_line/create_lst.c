/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 11:31:44 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/16 11:42:38 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"

/*
** petite fonction pour placer un element de la liste chainee en debut de liste
** puis change les valeur de la structure en fonction
*/

static void		insert_before(t_info *inf, t_arg *new)
{
	new->next = inf->arg;
	new->prev = NULL;
	inf->arg->prev = new;
	new->start = 1;
	new->current = 1;
	new->next->current = 0;
	new->next->start = 0;
	inf->arg = new;
}

/*
** trie par insertion de la liste chainee en fonction du code ascii des element
*/

static void		sort_ascii(t_info *inf, t_arg *new)
{
	t_arg		*tmp;
	t_arg		*tmp2;

	if (ft_strcmp(inf->arg->name, new->name) < 0)
	{
		tmp = inf->arg;
		while (inf->arg && ft_strcmp(inf->arg->name, new->name) < 0)
		{
			tmp2 = inf->arg;
			inf->arg = inf->arg->next;
		}
		new->next = tmp2->next;
		new->prev = tmp2;
		tmp2->next = new;
		inf->arg = tmp;
	}
	else
		insert_before(inf, new);
}

/*
** initialise un nouveau maillon avec les bonne valeur
*/

static void		new_node(char *av, t_info *info)
{
	t_arg		*new;

	if ((new = (t_arg *)malloc(sizeof(t_arg))))
	{
		new->name = ft_strdup(av);
		new->start = 0;
		new->current = 0;
		new->selected = 0;
		new->next = NULL;
		new->prev = NULL;
		sort_ascii(info, new);
	}
}

/*
** initialise le premier maillon avec les bonne valeur
*/

static void		init_node(char *av, t_info *info)
{
	if ((info->arg = (t_arg *)malloc(sizeof(t_arg))))
	{
		info->arg->start = 1;
		info->arg->name = ft_strdup(av);
		info->arg->current = 1;
		info->arg->selected = 0;
		info->arg->next = NULL;
		info->arg->prev = NULL;
	}
}

/*
** debut de la creation de la liste chainee de l'historic
*/

void			create_lst(char *av, t_info *info)
{
	if (info->arg == NULL)
		init_node(av, info);
	else
		new_node(av, info);
}
