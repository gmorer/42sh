/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 10:31:39 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/18 14:50:03 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "split.h"

char	**ft_shlvl(char **env)
{
	char	*line;
	int		i;
	char	*temp;

	if (!env)
	{
		env = ft_strstrnew(1);
		env[0] = "SHLVL=1";
		return (env);
	}
	if ((line = getenvline("SHLVL=")) == NULL)
	{
		env = ft_strstradd(ft_strdup("SHLVL=1"), env);
		return (env);
	}
	i = casenofor("SHLVL=");
	free(env[i]);
	temp = ft_itoa(ft_atoi(line) + 1);
	env[i] = ft_strjoin("SHLVL=", temp);
	free(temp);
	free(line);
	return (env);
}
