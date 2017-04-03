/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:35:54 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/30 11:55:01 by rvievill         ###   ########.fr       */
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

void			loop(void)
{
	char		*line;
	t_node		*tree;

	tree = NULL;
	while (1 && !(line = NULL))
	{
		g_shell->exec = 0;
		prompt();
		edit_line(&line, &(g_shell->hist), 0);
		line = ft_quote(line);
		if (line != NULL)
		{
			tree = mktree(parser(lexer(&line, line, 0)));
		}
		else
		{
			if (get_next_line(0, &line) <= 0)
				exit(0);
			line = ft_quote(line);
			tree = mktree(parser(lexer(&line, line, 0)));
		}
		g_shell->exec = 1;
		while ((tree = walkthrough(tree)))
			tree->ret_cmd = prep_exec(tree, g_shell->env);
	}
}

int				main(int ac, char **av)
{
	extern char	**environ;

	(void)ac;
	(void)av;
	init_mainprocess();
	g_shell->env = init_env(environ);
	g_shell->table = ft_init_hash_table();
	loop();
	ft_strstrfree(g_shell->env);
	return (0);
}
