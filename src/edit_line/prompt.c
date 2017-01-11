/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:10:32 by rvievill          #+#    #+#             */
/*   Updated: 2017/01/11 17:09:02 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include <time.h>
#include "minishell.h"
#include <sys/utsname.h>

t_shell		*shell;

void				path(void)
{
	char			*pwd;
	char			*home;
	char			*tmp;
	char			*new_path;

	pwd = NULL;
	new_path = NULL;
	home = NULL;
	tmp = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	ft_putstr(GREEN);
	if (!(home = getenvline(shell->env, "HOME=")))
		ft_putstr(pwd);
	else if ((tmp = ft_strstr(pwd, home)))
		new_path = ft_strjoin("~", tmp + ft_strlen(home));
	else
			new_path = ft_strdup(ft_strrchr(pwd, '/'));
	ft_putstr(new_path);
	free(tmp);
	free(home);
	free(new_path);
	ft_putstr(RED);
	ft_putendl(" ]");
	ft_putstr(DFL);
}

void				user(void)
{
	char			*user;
	struct utsname	post;
	char			*p;
	char			*tmp;

	ft_putstr(RED);
	ft_putstr("[ ");
	ft_putstr(GREEN);
	if (!(user = getenv("LOGNAME")))
		ft_putstr("Anonymous");
	ft_putstr(user);
	ft_putchar('@');
	uname(&post);
	tmp = ft_strchr(post.nodename, '.');
	p = ft_strsub(post.nodename, 0, (int)ft_strlen(tmp));
	ft_putstr(p);
	ft_putstr(": ");
	free(p);
}

void				arrow(void)
{
	ft_putstr(GREEN);
	ft_putstr("-> ");
	ft_putstr(DFL);
}

void				ft_time(void)
{
	char			*time_cur;
	time_t			t;

	time(&t);
	time_cur = ft_strsub(ctime(&t), 11, 5);
	ft_putstr(RED);
	ft_putstr("[ ");
	ft_putstr(GREEN);
	ft_putstr(time_cur);
	ft_putstr(DFL);
	ft_putstr(RED);
	ft_putstr(" ] ");
	ft_putstr(DFL);
	free(time_cur);
}

void				prompt(t_cursor *cur)
{
	(void)cur;
	ft_time();
	user();
	path();
	arrow();
}
