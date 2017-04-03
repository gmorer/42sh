/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 14:43:08 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 12:02:29 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			free_hist(t_hist *hist)
{
	t_hist	*tmp;

	while (hist)
	{
		tmp = hist->prev;
		free(hist->cmd);
		free(hist);
		hist = tmp;
	}
	return (0);
}

int			free_cursor(t_cursor *cursor)
{
	if (cursor)
	{
		ft_strdel(&cursor->line);
		ft_strdel(&cursor->str_cpy);
		free(cursor);
	}
	return (0);
}

int			free_binary(t_binary **table)
{
	t_binary	*tmp;

	while (*table)
	{
		tmp = *table;
		free((*table)->data);
		free(*table);
		*table = tmp->next;
	}
	free(table);
	return (0);
}

int			free_shell(void)
{
	if (g_shell)
	{
		if (g_shell->env)
		{
			ft_strstrfree(g_shell->env);
			g_shell->env = NULL;
		}
		if (g_shell->hist)
		{
			free_hist(g_shell->hist);
			g_shell->hist = NULL;
		}
		if (g_shell->table)
		{
			free_binary(g_shell->table);
			g_shell->table = NULL;
		}
		free(g_shell);
		g_shell = NULL;
	}
	return (0);
}
