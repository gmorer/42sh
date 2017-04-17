/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:17:33 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:17:34 by rvievill         ###   ########.fr       */
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
	i = casenofor("SHLVL");
	free(env[i]);
	temp = ft_itoa(ft_atoi(line) + 1);
	env[i] = ft_strjoin("SHLVL=", temp);
	ft_strdel(&temp);
	ft_strdel(&line);
	return (env);
}
