/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 11:43:44 by gmorer            #+#    #+#             */
/*   Updated: 2016/10/03 11:24:12 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		i;

	temp = NULL;
	test = NULL;
	prompt(env, returnvalue);
	i = get_next_line(1, &test);
	if (!test && i == 0)
		ft_putendl("exit");
	if (!test && i == 0)
		exit(0);
	if( !test && i == -1)
		ft_putchar('\n');
	if (test && test[0] && (temp = argvsplit(test)))
		temp = argvclean(temp, env);
	free(test);
	return (temp);
}

static int		boucle(char **env, char **temp, int returnvalue, t_binary **table)
{
	while (42)
	{
		ft_save_env(env);
		temp = getarg(env, returnvalue);
		if (temp && temp[0] && temp[0][0])
		{
			returnvalue = ft_redirect(temp, &env, &table);
			ft_strstrfree(temp);
			returnvaluetoenv(returnvalue, &env);
		}
		else
			returnvalue = 0;
	}
	return (1);
}

int				main(int argc, char **argv, char **env)
{
	char	**envdup;
	char	**temp;
	char	*bin;
	int		returnvalue;
	t_binary	**table;

	temp = NULL;
	bin = NULL;
	returnvalue = 0;
	table = NULL;
	//envdup = ft_strstrdup(env);
	envdup = init(env);
	(void)argv;
	(void)argc;
	ft_signal();
	table = ft_init_hash_table(&envdup);
	boucle(envdup, temp, returnvalue, table);
	return (0);
}
