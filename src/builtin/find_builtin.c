/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 14:06:19 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/07 13:14:02 by lvalenti         ###   ########.fr       */
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
		{"jobs", &ft_jobs},
		{"fg", &ft_fg},
		{"bg", &ft_bg},
		{"hashtab", &ft_hashtab},
		{"env", &ft_env},
		{"echo", &ft_echo},
		{"exit", &ft_exit}
	};

	i = 0;
	while (i < 10)
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
