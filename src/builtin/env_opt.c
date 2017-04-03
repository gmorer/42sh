/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 13:20:51 by lvalenti          #+#    #+#             */
/*   Updated: 2017/04/03 18:27:33 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "shell.h"
#include "env.h"
#include "exec.h"

t_shell		*g_shell;

void	show_env(void)
{
	int		i;

	i = 0;
	while (g_shell->env[i])
	{
		ft_putendl(g_shell->env[i]);
		i++;
	}
}

int		no_option(char **argv, t_detail *node, int j)
{
	pid_t		child;
	int			status;

	child = fork();
	if (child == 0)
	{
		node->argv = argv + j;
		exec_basic_cmd(node, g_shell->env, 1);
		exit(0);
	}
	else if (child > 0)
		waitpid(WAIT_ANY, &status, WUNTRACED);
	return (0);
}

int		option_v(char **argv, t_detail *node, int i)
{
	pid_t		child;
	int			status;

	ft_putstr("#env executing: ");
	ft_putendl(argv[i]);
	ft_putstr("#env    arg[0]= '");
	ft_putstr(argv[i]);
	ft_putendl("'");
	child = fork();
	if (child == 0)
	{
		node->argv = argv + 2;
		exec_basic_cmd(node, g_shell->env, 1);
		exit(0);
	}
	else if (child > 0)
		waitpid(WAIT_ANY, &status, WUNTRACED);
	return (0);
}

int		option_i(char **argv, t_detail *node)
{
	pid_t		child;
	int			status;

	child = fork();
	if (child == 0)
	{
		node->argv = argv + 2;
		exec_basic_cmd(node, NULL, 1);
		exit(0);
	}
	else if (child > 0)
		waitpid(WAIT_ANY, &status, WUNTRACED);
	return (0);
}

int		option_u(char **argv)
{
	int		i;

	if (ft_strstrlen(argv) != 2)
		return (1);
	if ((i = casenofor(argv[1])) == -1)
		return (1);
	if (ft_strcmp(argv[1], "BINARY_LEN") == 0)
		return (0);
	if (ft_strcmp(argv[1], "PATH") == 0)
		ft_free_hash_tab();
	g_shell->env = ft_strstrdelone(i, g_shell->env);
	return (0);
}
