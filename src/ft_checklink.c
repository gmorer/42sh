/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checklink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 11:05:28 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/02 13:42:23 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_checklink(char *path)
{
	struct stat tmp;
/*
	lstat(path, &tmp);
	if (!(S_ISLNK(tmp.st_mode)))
		return (1);*/
	if (stat(path, &tmp) == -1)
		return (0);
	return (1);
}
