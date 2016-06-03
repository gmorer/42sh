/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/03 16:58:02 by gmorer           ###   ########.fr       */
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

int		actuel_folder(char **str, char **env)
{
	char *temp;
	if (str && str[0] && str[0][0] && str[0][1] && str[0][0] == '.' && str[0][1] == '/')
	{
		temp = ft_strdup(str[0] + 2);
		free(str[0]);
		str[0] = temp;
		if(access(str[0], F_OK) == -1)
		{
			ft_putstr("./");
			ft_putstr(str[0]);
			ft_putendl(": Command not found.");
			return (1);
		}
		return (ft_exec(str[0], str, &env));
	}
	return (-1);
}

static void		returnvaluetoenv(int returnvalue, char ***env)
{
	char	**temp;

	//temp = NULL;
	temp = ft_strstrnew(3);
	temp[0] = ft_strdup("setenv");
	temp[1] = ft_strdup("?");
	temp[2] = ft_itoa(returnvalue);
	temp[3] = NULL;
	ft_setenv(temp, env);
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(temp);
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
		test = NULL;
		ft_putchar('[');
		ft_putnbr(returnvalue);
		ft_putchar(']');
		ft_putstr("prompt -> ");
		get_next_line(1, &test);
		if(test[0])
		{
		temp = argvsplit(test);
		temp = argvclean(temp, env);
		}
		if(test[0] && temp[0] && boucle == 42)
		{
			//temp = ft_strsplit(test, ' ');
			//temp = argvsplit(test);
			//temp = argvclean(temp, env);
			if((returnvalue = (actuel_folder(temp, env)) == -1))
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
				{
					returnvalue = ft_exec(bin, temp, &env);
					free(bin);
				}
			}
			ft_strstrfree(temp);
			returnvaluetoenv(returnvalue, &env);
		}
		//ft_putendl("test1");
		free(test);
		//ft_putendl("test2");
		//ft_putendl("test3");
	}
	ft_strstrfree(temp);
	if(env)
		ft_strstrfree(env);
	return (1);
}


int main(int argc, char **argv, char **env)
{
	char	**envdup;

	envdup = ft_strstrdup(env);
	(void)argv;
	(void)argc;
	boucle(envdup);
	return (0);
}
