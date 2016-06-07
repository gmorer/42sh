/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/06/07 14:49:50 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				actuel_folder(char **str, char **env)
{
	char *temp;

	if (str && str[0] && str[0][0] && str[0][1] && str[0][0] == '.' &&
			str[0][1] == '/')
	{
		temp = ft_strdup(str[0] + 2);
		free(str[0]);
		str[0] = temp;
		if (access(str[0], F_OK) == -1)
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

static char		**getarg(char **env, int returnvalue)
{
	char	**temp;
	char	*test;

	temp = NULL;
	test = NULL;
	prompt(env, returnvalue);
	get_next_line(1, &test);
	if (!test)
		ft_putendl("exit");
	if (!test)
		exit(0);
	if (test && test[0] && (temp = argvsplit(test)))
		temp = argvclean(temp, env);
	free(test);
	return (temp);
}

static int		boucle(char **env, char **temp, char *bin, int returnvalue)
{
	while (42)
	{
		temp = getarg(env, returnvalue);
		if (temp && temp[0] && temp[0][0])
		{
			if ((returnvalue = (actuel_folder(temp, env)) == -1))
				if ((returnvalue = (redirectfunction(temp, &env))) == -1)
				{
					bin = toexec(env, temp[0]);
					if (bin == NULL && (returnvalue = 1))
						ft_putendl("no binary file");
					else if ((returnvalue = ft_exec(bin, temp, &env)) || 1)
						free(bin);
				}
			ft_strstrfree(temp);
			returnvaluetoenv(returnvalue, &env);
		}
	}
	ft_strstrfree(temp);
	if (env)
		ft_strstrfree(env);
	return (1);
}

int				main(int argc, char **argv, char **env)
{
	char	**envdup;
	char	**temp;
	char	*bin;
	int		returnvalue;

	temp = NULL;
	bin = NULL;
	returnvalue = 0;
	signal(SIGINT, SIG_IGN);
	envdup = ft_strstrdup(env);
	(void)argv;
	(void)argc;
	boucle(envdup, temp, bin, returnvalue);
	return (0);
}
