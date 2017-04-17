/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:37:26 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:37:27 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisdigit(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '\n')
			return (0);
		str++;
	}
	return (1);
}
