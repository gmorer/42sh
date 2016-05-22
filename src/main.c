/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/20 16:35:56 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int		boucle(char **env)
{
	char	*test;
	char	**temp;
	pid_t	pid;
	int		exit;
	char	*bin;

	while(1)
	{
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &exit, 0);
		}
		if (pid == 0)
		{
			ft_putstr("prompt>");
			get_next_line(1, &test);
			temp = ft_strsplit(test, ' ');
			bin = ft_strdup(temp[0]);
			execve(ft_strjoin("/bin/",bin), temp, env);
		}
		ft_putendl("test1");
		free(test);
		ft_putendl("test2");
		//free(temp);
		ft_putendl("test3");
	}
		return (1);
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	boucle(env);
	ft_putendl("test3");
	return (0);
}
