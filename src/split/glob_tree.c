/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:22:04 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/27 12:45:18 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

int		need_glob_str(char *str)
{
	int	test;
	int	i;

	i = 0;
	test = 0;
	while (str[i] && str[i] != '/')
	{
		if (str[i] == '?' && is_reachable(str, i))
			return (1);
		if (str[i] == '*' && is_reachable(str, i))
			return (1);
		if (str[i] == '[' && is_reachable(str, i))
			test = 1;
		if (test == 1 && str[i] == ']' && is_reachable(str, i))
			return (1);
		i++;
	}
	return (0);
}

char	**glob_get_files(char *previous, char *matchvar, char *after, int *i)
{
	struct dirent	*file;
	DIR				*actualdir;
	char			**result;
	char			*temp;
	char			*temp1;

	if ((actualdir = opendir(previous ? previous : "./")) == NULL)
		return (NULL);
	result = ft_strstrnew(0);
	while ((file = readdir(actualdir)))
		if (match(file->d_name, matchvar) && file->d_name[0] != '.')
		{
			if (previous && ft_strcmp(previous, "/"))
				temp1 = ft_strjoin("/", file->d_name);
			else
				temp1 = ft_strdup(file->d_name);
			temp = ft_strjoin(previous, temp1);
			free(temp1);
			temp1 = ft_strjoin(temp, after);
			free(temp);
			result = ft_strstradd(temp1, result);
		}
	closedir(actualdir);
	*i = (result[0] ? *i : 0);
	return (result);
}

char	**resolve_glob(char **argv, int i, int ret)
{
	char	*after;
	char	*tp;
	char	*temp3;

	after = NULL;
	if (!(ret = get_pass(&argv, i, &tp, &temp3)))
	{
		ft_strstrfree(argv);
		free(tp);
		return (NULL);
	}
	while ((tp = ft_strchr(tp, '/')) != NULL)
	{
		if (need_glob_str(tp + 1))
		{
			after = trace_road(&argv, tp, &ret, i);
			if (after || !ret)
				free(after ? after : temp3);
			if (!ret)
				return (NULL);
		}
		tp++;
	}
	free(temp3);
	return (ft_strstrdelone(i, argv));
}

int		need_glob(char **str)
{
	int	i;
	int	x;
	int	test;

	x = 0;
	while (str[x] && !(i = 0))
	{
		test = 0;
		while (str[x][i])
		{
			if ((str[x][i] == '?' || str[x][i] == '*') &&
					is_reachable(str[x], i))
				return (x);
			if (str[x][i] == '[' && is_reachable(str[x], i))
				test = 1;
			if (test == 1 && str[x][i] == ']' && is_reachable(str[x], i))
				return (x);
			else
				i++;
		}
		x++;
	}
	return (-1);
}

char	**glob_result(char **argv)
{
	int		i;
	char	*temp;

	temp = NULL;
	if (!argv)
		return (NULL);
	while ((i = need_glob(argv)) != -1)
	{
		temp = ft_strdup(argv[i]);
		argv = resolve_glob(argv, i, 1);
		if (!argv)
		{
			ft_triplestr("21sh: no matches found: ", temp, "\n");
			free(temp);
			return (NULL);
		}
		free(temp);
	}
	return (argv);
}
