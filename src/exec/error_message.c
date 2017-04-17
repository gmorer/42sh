/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:18:50 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/08 11:57:37 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*error_message(int ret, char *cmd)
{
	if (!cmd)
		return (NULL);
	if (ret == 127)
	{
		ft_putstr_fd("42sh: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
	}
	else if (ret == 126 || ret == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied.", 2);
	}
	return (NULL);
}
