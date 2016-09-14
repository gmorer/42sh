/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 09:58:59 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/14 17:36:55 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_isin(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		folder(char **str, char **env)
{
	if (access(str[0], F_OK) == -1)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(str[0]);
		return (1);
	}
	if (access(str[0], X_OK) == -1)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl("str[0]");
		return (1);
	}
	return (ft_exec(str[0], str, &env));
}

int				ft_redirect(char **str, char ***env, t_binary **table)
{
	char	*bin;
	int		result;

	bin = NULL;
	if (ft_isin(str[0], '/'))
	{
		result = folder(str, *env);
		return (result);
	}
	if ((result = redirectfunction_builtin(str, env, table)) != -1)
		return (result);
	//bin = toexec(*env, str[0]);
	bin = ft_give_path(str[0], table, *env);
	if (bin)
	{
		result = ft_exec(bin, str, env);
		free(bin);
		return (result);
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(str[0]);
	return (127);
}
