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

int		boucle()
{
	char	*test;
	char	**temp;
	pid_t	father;
	int		exit;
	char	*bin;

	while(1)
	{
		father = fork();
		if (father > 0)
		{
			wait(&exit);
		}
		if (father == 0)
		{
			ft_putstr("prompt>");
			get_next_line(1, &test);
			temp = ft_strsplit(test, ' ');
			bin = ft_strdup(temp[0]);
			execve(ft_strjoin("/bin/",bin), temp, NULL);
		}
		free(test);
		free(temp);
	}
		return (1);
}

int main()
{

	boucle();
	ft_putendl("test3");
	return (0);
}
