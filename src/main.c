/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2017/01/05 15:11:25 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		*shell;

static void		returnvaluetoenv(int returnvalue, char ***env)
{
	char	**temp;

	temp = ft_strstrnew(3);
	temp[0] = ft_strdup("setenv");
	temp[1] = ft_strdup("?");
	temp[2] = ft_itoa(returnvalue);
	temp[3] = NULL;
	ft_setenv(temp, env, NULL);
	free(temp[0]);
	free(temp[1]);
	free(temp[2]);
	free(temp);
}

static char		**getarg(char **env, int returnvalue)
{
	char	**temp;
	char	*test;
	//int		i;

	temp = NULL;
	test = NULL;
	ft_prompt(env, returnvalue);
	edit_line(&test, &(shell->hist));
	/*
	i = get_next_line(1, &test);
	if (!test && i == 0)
		ft_putendl("exit");
	if (!test && i == 0)
		exit(0);
	if( !test && i == -1)
		ft_putchar('\n');
		*/
	if (test && test[0] && (temp = argvsplit(test)))
	{
		temp = argvclean(temp);
		temp = glob_result(temp);/*
		ft_putendl("//////argv://////");
		ft_putmap(temp);
		ft_putendl("/////////////////");*/
	}
	free(test);
	return (temp);
}

int			boucle(char **temp, int returnvalue, t_binary **table)
{
	while (42)
	{
		//ft_save_env(env);
		temp = getarg(shell->env, returnvalue);
		if (temp && temp[0] && temp[0][0])
		{
			returnvalue = ft_redirect(temp, &(shell->env), &table);
			ft_strstrfree(temp);
			returnvaluetoenv(returnvalue, &(shell->env));
		}
		else
			returnvalue = 0;
	}
//	return (1);
}

int				main(int argc, char **argv, char **env)
{
	extern char	**environ;
	char	**temp;
	char	*bin;
	int		returnvalue;

	(void)env;
	temp = NULL;
	bin = NULL;
	returnvalue = 0;
	shell = NULL;
	init_mainprocess();
	shell->env = ft_strstrdup(environ);
	//envdup = init(environ);
	(void)argv;
	(void)argc;
	ft_signal();
	shell->table = ft_init_hash_table(&(shell->env));
	boucle(temp, returnvalue, shell->table);
	return (0);
}
