/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:10:32 by rvievill          #+#    #+#             */
/*   Updated: 2017/03/08 13:04:23 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit_line.h"
#include <time.h>
#include "env.h"
#include <sys/utsname.h>

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
	pwd = getcwd(pwd, 0);
	pwd = pwd ? pwd : "no_where";
	ft_putstr(GREEN);
	if (pwd && !(home = getenvline("HOME=")))
		ft_putstr(pwd);
	else if (home && pwd && (tmp = ft_strstr(pwd, home)))
		ft_putstr(new_path = ft_strjoin("~", tmp + ft_strlen(home)));
	else if (pwd)
		ft_putstr(new_path = ft_strdup(ft_strrchr(pwd, '/')));
	else
		ft_putstr(new_path = ft_strdup("no_where"));
	if (tmp)
		free(tmp);
	if (home)
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
	if (!(user = getenvline("USER")))
		ft_putstr("Anonymous");
	else
	{
		ft_putstr(user);
		free(user);
	}
	ft_putchar('@');
	uname(&post);
	if ((tmp = ft_strchr(post.nodename, '.')))
		*tmp = '\0';
	p = ft_strdup(post.nodename);
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

void				prompt(void)
{
	ft_time();
	user();
	path();
	arrow();
}
