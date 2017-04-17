/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 19:00:59 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/17 15:11:33 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include "lex_par_ast.h"
#include "shell.h"
#include "env.h"
#include "hashtab.h"
#include "split.h"
#include <stdio.h>
#include "errno.h"

t_shell		*g_shell;

static void		add_ret(int i)
{
	char *temp;

	temp = ft_itoa(i);
	replace_env("?", "?=", temp);
	free(temp);
}

void			loop(t_node *tree)
{
	char		*line;

	while (1 && !(line = NULL))
	{
		g_shell->av = NULL;
		g_shell->exec = 0;
		prompt();
		if (edit_line(&line, &(g_shell->hist), 0) == -1)
		{
			g_shell->cursor = NULL;
			get_next_line(0, &line);
		}
		if ((line = ft_quote(line)) != NULL)
			tree = mktree(parser(lexer(&line, line, 0)));
		else
			exit(0);
		g_shell->exec = 1;
		while ((tree = walkthrough(tree)))
		{
			tree->ret_cmd = prep_exec(tree, g_shell->env);
			add_ret(tree->ret_cmd);
		}
		job_quit(9);
	}
}

int				main(int ac, char **av)
{
	extern char	**environ;
	t_node		*tree;

	tree = NULL;
	(void)ac;
	(void)av;
	if (isatty(0) != 1 || isatty(1) != 1 || isatty(2) != 1)
		return (0);
	init_mainprocess();
	g_shell->env = init_env(environ);
	g_shell->table = ft_init_hash_table();
	g_shell->heredoc = 0;
	add_ret(0);
	loop(tree);
	ft_strstrfree(g_shell->env);
	return (0);
}
