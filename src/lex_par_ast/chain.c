/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:51:01 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/17 15:05:24 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "libft.h"
#include "split.h"
#include "shell.h"

t_shell		*g_shell;

static t_detail	*add_detail(t_detail *list, t_detail *new)
{
	t_detail	*temp;
	int			i;

	i = 0;
	while (new && new->argv && new->argv[i])
	{
		new->argv[i] = argvtest(new->argv[i]);
		i++;
	}
	if (list == NULL)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (list);
}

int				is_not_quote(char *str, int i)
{
	int		j;

	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '\'' && (j == 0 || str[j - 1] != '\\' ||
					(str[j - 1] == '\\' && !is_reachable(str, j - 1))) &&
					!g_shell->quote[1])
		{
			g_shell->quote[0] = 1 - g_shell->quote[0];
		}
		if (str[j] == '"' && (j == 0 || str[j - 1] != '\\' ||
					(str[j - 1] == '\\' && !is_reachable(str, j - 1))) &&
					!g_shell->quote[0])
		{
			g_shell->quote[1] = 1 - g_shell->quote[1];
		}
		j++;
	}
	if (g_shell->quote[0] || g_shell->quote[1])
		return (0);
	else
		return (1);
}

int				get_redir_line(int start, int end, char **str)
{
	size_t	i;
	char	*temp;

	i = start;
	if (!str || i >= ft_strstrlen(str))
		return (-1);
	while (start < end)
	{
		if ((temp = (ft_strstr(str[start], ">"))) ||
				(temp = (ft_strstr(str[start], "<"))))
		{
			if (is_reachable(str[start], temp - str[start]))
				return (start);
		}
		start++;
	}
	return (-1);
}

static t_detail	*remp_detail(int start, int *end, char ***str, t_detail *list)
{
	t_detail	*new;
	int			i;

	new = (t_detail*)malloc(sizeof(t_detail));
	*new = (t_detail){NULL, NULL, 0, NULL, NULL, NULL, {0, 0}, NULL, NULL};
	while ((i = get_redir_line(start, *end, *str)) != -1 && (*end)--)
	{
		new->redir_str = ft_strstradd(
				argvtest(ft_strdup((*str)[i])), new->redir_str);
		*str = ft_strstrdelone(i, *str);
	}
	i = start - 1;
	new->pipe = (ft_strcmp((*str)[*end], "|") == 0 ? 1 : 0);
	new->argv = *end - start + 1 > 1 ?
		(char**)malloc(sizeof(char*) * (*end - start + 1)) : NULL;
	new->redir = (int*)malloc(sizeof(int) * ft_strstrlen(new->redir_str));
	ft_bzero(new->redir, sizeof(int) * ft_strstrlen(new->redir_str));
	while (++i < *end && new->argv)
		new->argv[i - start] = ft_strdup((*str)[i]);
	new->argv ? new->argv[i - start] = NULL : NULL;
	new->fd_std = (int *)malloc(sizeof(int) * ft_strstrlen(new->redir_str));
	new->fd_file = (int *)malloc(sizeof(int) * ft_strstrlen(new->redir_str));
	ft_memset(new->fd_std, -1, sizeof(int) * ft_strstrlen(new->redir_str));
	ft_memset(new->fd_file, -1, sizeof(int) * ft_strstrlen(new->redir_str));
	return (add_detail(list, new));
}

t_detail		*str_to_lst(char *str)
{
	char		**temp;
	t_detail	*list;
	int			start;
	int			i;

	if (!str || !(temp = argvsplit(str, 7)))
		return (NULL);
	i = 0;
	list = NULL;
	while (temp[i])
	{
		start = i;
		while (temp[i] && ft_strcmp(temp[i], "|") != 0)
			i++;
		list = remp_detail(start, &i, &temp, list);
		if (i > (int)ft_strstrlen(temp) || temp[i] == NULL)
		{
			ft_strstrfree(temp);
			return (list);
		}
		i++;
	}
	ft_strstrfree(temp);
	return (list);
}
