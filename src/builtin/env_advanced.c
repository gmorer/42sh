/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_advanced.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:09:34 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/17 14:13:49 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		print_arg(char **argv, int i)
{
	while (argv[i])
	{
		ft_putendl(argv[i]);
		i++;
	}
}

int			verif_opt(t_option comp)
{
	if (comp.opt_i || comp.opt_u || comp.opt_v)
		return (0);
	return (1);
}

char		**temp_env(char **env, char *str)
{
	char	*s3;
	char	*s1;
	char	*s2;

	(void)env;
	if (!str)
		return (NULL);
	s1 = ft_strchr(str, '=');
	s1++;
	s2 = ft_strndup(str, ft_strlen(str) - ft_strlen(s1) - 1);
	s3 = ft_strjoin(s2, "=");
	replace_env(s2, s3, s1);
	free(s2);
	free(s3);
	return (NULL);
}

int			check_variable(char *var)
{
	if (ft_strlen(var) == 1)
	{
		if (*var != '=')
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd("No such file or directory", 2);
		}
		else
			ft_putstr_fd("env: setenv =: Invalid argument", 2);
		return (0);
	}
	else if (*var == '=')
	{
		ft_putstr_fd("env: setenv ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(": Invalid argument", 2);
		return (0);
	}
	return (1);
}
