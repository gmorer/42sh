/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:10:29 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 21:06:45 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"
#include "exec.h"

t_shell		*g_shell;

static int		recup_opt(char **argv, int i, int j, t_option *comp)
{
	if (argv[i][j] == 'i')
		comp->opt_i = 1;
	else
	{
		ft_putstr("env: illegal option -- ");
		ft_putchar(argv[i][j]);
		ft_putchar('\n');
		return (1);
	}
	return (0);
}

int				exec_env(char **argv, t_option comp, int i)
{
	if (ft_strstr(argv[i], "=") == NULL && verif_opt(comp) == 1)
		return (no_option(argv, i));
	else if (ft_strstr(argv[i], "=") && ft_strncmp(argv[i], "=", 1) != 0)
	{
		if (comp.opt_i)
			print_arg(argv, i);
		else
		{
			show_env();
			print_arg(argv, i);
		}
	}
	else if (comp.opt_i)
		return (option_i(argv, i));
	return (0);
}

static int		env_option(char **argv, t_option *comp)
{
	int			i;
	int			j;

	i = 1;
	if (argv[i][0] == '-' && !argv[i][1])
		return (-1);
	while (argv[i] && argv[i][0] == '-' && argv[i][0])
	{
		j = 1;
		if (!ft_strcmp(argv[i], "--"))
			return (1);
		if (argv[i][1] == '\0')
		{
			comp->opt_i = 1;
			return (0);
		}
		while (argv[i][j])
		{
			if (recup_opt(argv, i, j, comp) == 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (i);
}

int				ft_env(char **argv)
{
	int			i;
	t_option	comp;
	int			j;

	i = ft_strstrlen(argv);
	if (i < 2)
		show_env();
	else
	{
		comp = (t_option) {0, 0, 0, 0, 0};
		if ((i = env_option(argv, &comp)) == -1)
			return (1);
		j = i - 1;
		while (argv[++j])
		{
			if (!check_variable(argv[i]))
				return (1);
			if (argv[j] && !ft_strstr(argv[j], "="))
				return (exec_env(argv, comp, j));
		}
		return (exec_env(argv, comp, i));
	}
	return (0);
}
