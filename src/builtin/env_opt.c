/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 11:04:03 by lvalenti          #+#    #+#             */
/*   Updated: 2017/04/17 14:12:17 by gmorer           ###   ########.fr       */
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
	while (g_shell->env && g_shell->env[i])
	{
		ft_putendl(g_shell->env[i]);
		i++;
	}
}

int		no_option(char **argv, int j)
{
	int			i;
	char		**old_env;
	t_detail	node;
	pid_t		pid;

	i = 0;
	old_env = ft_strstrdup(g_shell->env);
	while (++i < j)
		temp_env(g_shell->env, argv[i]);
	node.argv = argv + j;
	if ((pid = fork()) == 0)
		exec_basic_cmd(&node, g_shell->env, 1, 0);
	else
		waitpid(pid, &i, WUNTRACED);
	ft_strstrfree(g_shell->env);
	g_shell->env = old_env;
	if (WIFEXITED(i))
		return (WEXITSTATUS(i));
	return (WIFSIGNALED(i) ? WTERMSIG(i) : i);
}

int		option_i(char **argv, int i)
{
	int			status;
	t_detail	node;
	pid_t		pid;

	status = 0;
	node.argv = argv + i;
	if ((pid = fork()) == 0)
		exec_basic_cmd(&node, NULL, 1, 0);
	else
		waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WIFSIGNALED(status) ? WTERMSIG(status) : status);
}
