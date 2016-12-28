/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 16:10:32 by rvievill          #+#    #+#             */
/*   Updated: 2016/12/28 15:24:35 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/edit_line.h"
#include <time.h>
#include <sys/utsname.h>

void				path(void)
{
	char			*pwd;
	char			*new_path;
	char			*tilde;
	char			*tmp;

	pwd = NULL;
	tilde = ft_strdup("~");
	pwd = getcwd(pwd, sizeof(pwd));
	tmp = ft_strsub(pwd, 20, ft_strlen(pwd) - 19);
	new_path = ft_strjoin(tilde, tmp);
	ft_putstr(new_path);
	ft_putstr(RED);
	ft_putstr(" ]\n");
	ft_putstr(DFL);
	free(new_path);
	free(pwd);
	free(tmp);
}

void				user(void)
{
	char			*user;
	struct utsname	post;
	char			*p;

	ft_putstr(RED);
	ft_putstr("[ ");
	ft_putstr(GREEN);
	if (!(user = getenv("LOGNAME")))
		ft_putstr("Anonymous");
	ft_putstr(user);
	ft_putchar('@');
	uname(&post);
	p = ft_strsub(post.nodename, 0, 6);
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
