/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:56:31 by gmorer            #+#    #+#             */
/*   Updated: 2016/09/15 12:59:44 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_binary	*ft_remp(t_binary *bin, char *binary, char *path)
{
	char *temp;
	
	temp = NULL;
	if (!(bin->data = malloc(sizeof(t_data))))
		return (NULL);
	bin->data->name = ft_strdup(binary);
	temp = ft_strjoin(path, "/");
	bin->data->full_path = ft_strjoin(temp, binary);
	free(temp);
	return (bin);
}

t_binary	**ft_add_hash_to_tab(char *binary, char *path, t_binary **table, char **env)
{
	int	result;
	t_binary *last;
//////////////////////////////////////
	ft_putstr("adding ");
	ft_putstr(path);
	ft_putchar('/');
	ft_putstr(binary);
//////////////////////////////////////
	if ((result = ft_hash_algo(binary, env)) == -1)
	{
		ft_putendl("Cannot add hash to table");
		return (NULL);
	}
	ft_putstr("... hash ->");
	ft_putnbr(result);
	if (table[result]->data == NULL)
	{
		ft_putstr(" -> new tab");
		ft_remp(table[result], binary, path);
	}
	else
	{
		last = table[result];
		ft_putstr(" -> existing tab");
		while ((last->next))
			last = last->next;
		if (!(last->next = malloc(sizeof(t_binary))))
			return (NULL);
		ft_remp(last->next, binary, path);
		last->next->next = NULL;
	}
	ft_putendl(": ok");
	return (table);
}

static t_binary	**ft_remp_table_dir(char *path, t_binary **table, char **env)
{
	DIR	*directory;
	struct	dirent *file;

	if (!(directory = opendir(path)))
		return (table);
	while ((file = readdir(directory)))
		if (file->d_name[0] != '.')
			table = ft_add_hash_to_tab(file->d_name, path, table , env);
	closedir(directory);
	return (table);
}

t_binary	**ft_remp_table(t_binary **table, char **env)
{
	char	*temp1;
	char	**temp2;
	int	i;

	i = 0;
	if(!(temp1 = getenvline(env, "PATH=")))
		return (NULL);
	temp2 = ft_strsplit(temp1, ':');
	free(temp1);
	while (temp2[i])
	{
		table = ft_remp_table_dir(temp2[i], table, env);
		free(temp2[i]);
		i++;
	}
	free(temp2);
	return (table);
}

t_binary	**ft_init_hash_table(char ***env)
{
	t_binary	**result;
	int		i;
	char		**temp;

	i = ft_count_binary(*env);
	if (!(result = (t_binary**)malloc(sizeof(t_binary*) * ((unsigned long)i + 1))))
		return (NULL);
	temp = ft_strstrnew(3);
	temp[0] = ft_strdup("setenv");
	temp[1] = ft_strdup("BINARY_LEN");
	temp[2]	= ft_itoa(i);
	temp[3] = NULL;
	ft_setenv(temp, env);
	ft_strstrfree(temp);
	result[i] = NULL;
	while ( i >= 0)
	{
		if (!(result[i] = (t_binary*)malloc(sizeof(t_binary))))
			return(NULL);
		result[i]->data = NULL;
		result[i]->next = NULL;
		i--;
	}
	result = ft_remp_table(result, *env);
	return (result);
}
