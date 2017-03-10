/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:35:54 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/09 17:17:18 by gmorer           ###   ########.fr       */
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
	t_hist		*hist;
	t_node		*tree;

	tree = NULL;
	hist = NULL;
	while (1)
	{
		job_quit(9);
		line = NULL;
		prompt();
		edit_line(&line, &hist);
		line = ft_quote(line);
		if (line != NULL)
			tree = mktree(parser(lexer(line, line, 0)));
		else
		{
			if (get_next_line(0, &line) == 0)
				exit(0);
			line = ft_quote(line);
			tree = mktree(parser(lexer(ft_strdup(line), line, 0)));
		}
		while ((tree = walkthrough(tree)))
			tree->ret_cmd = prep_exec(tree, g_shell->env);
	}
	free(line);
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
	return (0);
}
