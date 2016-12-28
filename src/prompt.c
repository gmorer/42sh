/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 15:23:40 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/28 15:24:25 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*shell;

static void	allenv(char *temp, char *temp1, char *temp2)
{
	if (ft_strstr(temp, temp1) != NULL)
	{
		ft_putstr("\x1b[31m");
		ft_putstr(temp2);
		ft_putstr("\x1b[32m");
		ft_putstr(temp + ft_strlen(temp1));
		shell->prompt_len += ft_strlen(temp2) + ft_strlen(temp + ft_strlen(temp1));
	}
	else
	{
		ft_putstr("\x1b[32m");
		ft_putstr(temp);
		shell->prompt_len += ft_strlen(temp);
	}
}

static char	*promptinit(char **env, int returnvalue, char **temp1, char **temp2)
{
	char	*temp;

	temp = ft_itoa(returnvalue);
	ft_putstr("\x1b[34m[\e[1m");
	ft_putstr(temp);
	shell->prompt_len += 6 + ft_strlen(temp);
	free(temp);
	ft_putstr("]\x1b[33m -> ");
	temp = getcwd(NULL, 0);
	*temp1 = getenvline(env, "HOME=");
	*temp2 = getenvline(env, "USER=");
	return (temp);
}

void		ft_prompt(char **env, int returnvalue)
{
	char	*temp1;
	char	*temp2;
	char	*temp;

	shell->prompt_len = 2;
	temp1 = NULL;
	temp2 = NULL;
	temp = promptinit(env, returnvalue, &temp1, &temp2);
	if (temp1 && temp)
	{
		if (temp2)
			allenv(temp, temp1, temp2);
		if (temp2)
			free(temp1);
		free(temp2);
	}
	else if (temp)
	{
		ft_putstr("\x1b[32m");
		ft_putstr(temp);
		shell->prompt_len += ft_strlen(temp);
		if (temp2)
			free(temp2);
	}
	if (temp)
		free(temp);
	else if ((shell->prompt_len += 5) || (1 == 1))
		ft_putstr(". -> ");
	ft_putstr("\x1b[36m: \x1b[0m\n-> ");
}
