/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:10:00 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/12 10:58:06 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "libft.h"

int		builtin(t_detail *node)
{
	int					i;
	static t_builtin	tab[10] = {
		{"cd", &ft_cd},
		{"setenv", &ft_setenv},
		{"unsetenv", &ft_unsetenv},
		{"hashtab", &ft_hashtab},
		{"fg", &ft_fg},
		{"bg", &ft_bg},
		{"jobs", &ft_jobs},
		{"env", &ft_env},
		{"echo", &ft_echo},
		{"exit", &ft_exit}
	};

	i = 0;
	while (i < 10 && node->argv)
	{
		if (ft_strcmp(node->argv[0], tab[i].name) == 0)
		{
			linkio(node);
			return (tab[i].fbuiltin(node->argv));
		}
		i++;
	}
	return (-1);
}
