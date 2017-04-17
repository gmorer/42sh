/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:19:45 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 20:44:58 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include <exec.h>
#include <fcntl.h>
#include "env.h"
#include "edit_line.h"
#include "lex_par_ast.h"
#include <unistd.h>

t_shell				*g_shell;

char			*get_file(char *str)
{
	int					i;

	i = ft_strlen(str);
	while (i > 0 && str[i - 1] != '>' && str[i - 1] != '<'
			&& str[i - 1] != ' ' && str[i - 1] != '&')
		i--;
	return (str[i] ? ft_strdup(&str[i]) : NULL);
}

int				redir_right(t_detail *node, int type, char *arg, int i)
{
	struct stat			file;

	node->fd_std[i] = STDOUT_FILENO;
	if (node->redir_str[i][0] != '>' && node->redir_str[i][0] != ' ')
		node->fd_std[i] = ft_atoi(node->redir_str[i]);
	if (ft_strisdigit(arg) || !ft_strcmp(arg, "-"))
	{
		ft_strisdigit(arg) ? node->fd_file[i] = ft_atoi(arg) :
			close(node->fd_std[i]);
		return (0);
	}
	else if ((lstat(arg, &file)) == -1)
		node->fd_file[i] = open(arg, O_CREAT, 0644);
	else if (access(arg, W_OK) == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (1);
	}
	node->fd_file[i] = (type == DB_R) ? open(arg, O_RDWR | O_APPEND)
		: open(arg, O_WRONLY | O_TRUNC);
	return (node->fd_file[i] == -1 ? 1 : 0);
}

int				sl_redir(t_detail *node, int type, char *file, int i)
{
	struct stat			info;

	(void)type;
	node->fd_std[i] = STDIN_FILENO;
	if (node->redir_str[i][0] != '<' && node->redir_str[i][0] != ' ')
		node->fd_std[i] = ft_atoi(node->redir_str[i]);
	if (ft_strisdigit(file) || !ft_strcmp(file, "-"))
		ft_strisdigit(file) ? node->fd_std[i] = ft_atoi(file) :
			close(node->fd_std[i]);
	if (ft_strisdigit(file) || !ft_strcmp(file, "-"))
		return (0);
	if ((node->fd_file[i] = open(file, O_RDONLY)) != -1)
		return (0);
	else if ((lstat(file, &info)) == -1)
	{
		ft_putstr_fd("42sh: no such file or directory: ", 2);
		ft_putendl_fd(file, 2);
	}
	else if (access(file, W_OK) == -1)
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	return (1);
}

int				heredoc(t_detail *node, int type, char *end, int i)
{
	char				*line;

	(void)type;
	line = NULL;
	g_shell->heredoc = 1;
	node->fd_std[i] = STDIN_FILENO;
	if (node->redir_str[i][0] != '<' && node->redir_str[i][0] != ' ')
		node->fd_std[i] = ft_atoi(node->redir_str[i]);
	if (pipe(node->pfd) == -1)
		return (1);
	while (1)
	{
		ft_putstr_fd("h> ", 2);
		if (edit_line(&line, NULL, 1) == -1)
			if (get_next_line(0, &line) < 0)
				return (1);
		if (!line || ft_strcmp(line, end) == 0)
			break ;
		ft_putendl_fd(line, node->pfd[1]);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	close(node->pfd[1]);
	return (!g_shell->heredoc ? 1 : 0);
}

int				select_redir(t_node *tree)
{
	t_detail			*tmp;
	char				*file;
	int					i;
	static int			(*redir[4])(t_detail *, int, char *, int) =
	{redir_right, redir_right, sl_redir, heredoc};

	tmp = tree->lst;
	while (tmp)
	{
		i = -1;
		while (tmp->redir_str && tmp->redir_str[++i])
		{
			file = get_file(tmp->redir_str[i]);
			if (i > -1 && tmp->redir[i] != DB_L
				&& redir[tmp->redir[i]](tmp, tmp->redir[i], file, i))
			{
				ft_strdel(&file);
				return (1);
			}
			ft_strdel(&file);
		}
		tmp = tmp->next;
	}
	return (0);
}
