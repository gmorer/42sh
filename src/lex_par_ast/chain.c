/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 14:29:40 by lvalenti          #+#    #+#             */
/*   Updated: 2017/03/09 10:37:58 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex_par_ast.h"
#include "libft.h"
#include "split.h"
#include "shell.h"

t_shell		*g_shell;

static t_detail	*add_detail(t_detail *list, t_detail *new)
{
	t_detail *temp;

	if (list == NULL)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	return (list);
}

/* return 0 if you are in quote and 1 if not */

int				is_not_quote(char *str, int i)
{
	int		j;
	//int		quote[2];

	//quote[0] = 0;
	//quote[1] = 0;
	j = 0;
	while (str[j] && j < i)
	{
		if (str[j] == '\'' && is_reachable(str, j))
			g_shell->quote[0] = 1 - g_shell->quote[0];
		if (str[j] == '"' && is_reachable(str, j))
			g_shell->quote[1] = 1 - g_shell->quote[1];
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
		if (((temp = (ft_strstr(str[start], ">"))) ||
		(temp = (ft_strstr(str[start], "<")))) &&
		is_not_quote(str[start], temp - str[start]))
		{
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
	int			j;
	size_t		len;

	new = (t_detail*)malloc(sizeof(t_detail));
	*new = (t_detail){NULL, NULL, 0, NULL, NULL, NULL, {0, 0}, NULL, NULL};
	j = start;
	while ((i = get_redir_line(j, *end, *str)) != -1)
	{
		new->redir_str = ft_strstradd(ft_strdup((*str)[i]), new->redir_str);
		*str = ft_strstrdelone(i, *str);
		(*end)--;
	}
	i = start - 1;
	new->pipe = (ft_strcmp((*str)[*end], "|") == 0 ? 1 : 0);
	new->argv = (char**)malloc(sizeof(char*) * (*end - start + 1));
	new->redir = (int*)malloc(sizeof(int) * ft_strstrlen(new->redir_str));
	ft_bzero(new->redir, ft_strstrlen(new->redir_str));
	while (++i < *end)
		new->argv[i - start] = ft_strdup((*str)[i]);
	new->argv[i - start] = NULL;
	len = ft_strstrlen(new->redir_str);
	new->fd_std = (int *)malloc(sizeof(int) * len);
	new->fd_file = (int *)malloc(sizeof(int) * len);
	ft_memset(new->fd_std, -1, len);
	ft_memset(new->fd_file, -1, len);
	return (add_detail(list, new));
}

t_detail		*str_to_lst(char *str)
{
	char		**temp;
	t_detail	*list;
	int			start;
	int			i;

	if (!str)
		return (NULL);
	i = 0;
	list = NULL;
	temp = argvsplit(str, 7);
	if (!temp)
		return (NULL);
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
	return (list);
}
