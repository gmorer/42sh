/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/05/30 17:45:09 by gmorer           ###   ########.fr       */
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

static int		boucle(char **env)
{
	char	*test;
	char	**temp;
	char	*bin;
	int		boucle;
	int		returnvalue;

	returnvalue = 0;
	//char	*yolo = "test $HOME yolo";
	//ft_putendl(ft_strstr(yolo, "$HOME"));
	boucle = 42;
	while(boucle == 42)
	{
		ft_putchar('[');
		ft_putnbr(returnvalue);
		ft_putchar(']');
		ft_putstr("prompt -> ");
		get_next_line(1, &test);
		ft_strcmp(test, "exit") == 0 ? boucle = 0 : 0;
		temp = argvsplit(test);
		temp = argvclean(temp, env);
		if(temp[0] && boucle == 42)
		{
			//temp = ft_strsplit(test, ' ');
			//temp = argvsplit(test);
			//temp = argvclean(temp, env);
			if((returnvalue = (redirectfunction(temp, &env))) == -1)
			{
				bin = toexec(env, temp[0]);
				//ft_putendl(bin);
				if (bin == NULL)
				{
					returnvalue = 1;
					ft_putendl("no binary file");
				}
				else
					returnvalue = ft_exec(bin, temp, &env);
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
	char	**envdup;

	envdup = ft_strstrdup(env);
	(void)argv;
	(void)argc;
	boucle(env);
	return (0);
}
