/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/23 17:32:39 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strstrfree(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		boucle(char **env)
{
	char	*test;
	char	**temp;
	char	*bin;
	int		boucle;

	boucle = 42;
	while(boucle == 42)
	{
		ft_putstr("prompt -> ");
		get_next_line(1, &test);
		ft_strcmp(test, "exit") == 0 ? boucle = 0 : 0;
		if(test[0] && boucle == 42)
		{
			temp = ft_strsplit(test, ' ');
			bin = toexec(env, temp[0]);
			if (bin == NULL)
			{
				ft_putendl("test");
				redirectfunction(temp, env);
				ft_putendl("no binary file");
			}
			else
			{
				ft_putendl("test1");
				ft_exec(bin, temp, env);
			}
			ft_strstrfree(temp);
		}
		//ft_putendl("test1");
		free(test);
		//ft_putendl("test2");
		//ft_putendl("test3");
	}
		return (1);
}


int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	boucle(env);
	return (0);
}
