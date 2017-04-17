/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfolder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:30:01 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/15 14:59:37 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isfolder(char *path)
{
	struct stat file;

	if ((stat(path, &file)) == -1)
		return (-1);
	if (S_ISDIR(file.st_mode) == 1)
		return (0);
	return (1);
}
