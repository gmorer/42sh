/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 13:32:46 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/23 17:17:05 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

char	*ft_quote(char *av, int test[2])
{
	char	*result;
	char	*buff;
	char	*tmp;

	tmp = NULL;
	//ft_putstr("debut de av: ");
	//ft_putendl(av);
	if (test[0])
		ft_putstr("quote> ");
	else
		ft_putstr("dquote> ");
	edit_line(&buff, &(shell->hist));/*
	if (i == 0)
	{
		return (av);
	}*/
	tmp = ft_strjoin(buff, "\n");
	result = ft_strjoin(av, tmp);
	free(tmp);
	//ft_putstr("fin de rslt: ");
	//ft_putendl(result);
	return (result);
}
