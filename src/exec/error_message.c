/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:56:03 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/03 15:39:16 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*error_message(int ret, char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ret == 127)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else if (ret == 126 || ret == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied.", 2);
	}
	return (NULL);
}
