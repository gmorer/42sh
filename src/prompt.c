/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:23:40 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/01 15:40:35 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	allenv(char *temp, char *temp1, char *temp2)
{
	if (ft_strstr(temp, temp1) != NULL)
	{
		ft_putstr("\x1b[31m");
		ft_putstr(temp2);
		ft_putstr("\x1b[32m");
		ft_putstr(temp + ft_strlen(temp1));
	}
	else
	{
		ft_putstr("\x1b[32m");
		ft_putstr(temp);
	}
}

static char	*promptinit(char **env, int returnvalue, char **temp1, char **temp2)
{
	char	*temp;

	ft_putstr("\x1b[34m[\e[1m");
	ft_putnbr(returnvalue);
	ft_putstr("]\x1b[33m -> ");
	temp = getcwd(NULL, 0);
	*temp1 = getenvline(env, "HOME=");
	*temp2 = getenvline(env, "USER=");
	return (temp);
}

void		prompt(char **env, int returnvalue)
{
	char	*temp1;
	char	*temp2;
	char	*temp;

	temp1 = NULL;
	temp2 = NULL;
	temp = promptinit(env, returnvalue, &temp1, &temp2);
	if (temp1)
	{
		if (temp2)
			allenv(temp, temp1, temp2);
		if (temp2)
			free(temp1);
		free(temp2);
	}
	else
	{
		ft_putstr("\x1b[32m");
		ft_putstr(temp);
		if (temp2)
			free(temp2);
	}
	free(temp);
	ft_putstr("\x1b[36m: \x1b[0m");
}
