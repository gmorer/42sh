/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:58 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 14:44:28 by gmorer           ###   ########.fr       */
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
		if ((str[i] == '?' || str[i] == '*' || str[i] == '[' || str[i] == ']')
				&& is_reachable(str, i))
		{
			if (str[i] == '[')
				test = 1;
			else if (str[i] == ']' && test == 1)
				return (1);
			else
				return (1);
		}
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
			ft_strdel(&temp1);
			temp1 = ft_strjoin(temp, after);
			ft_strdel(&temp);
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

	if (!(ret = get_pass(&argv, i, &tp, &temp3)))
	{
		ft_strstrfree(argv);
		ft_strdel(&tp);
		return (NULL);
	}
	while ((tp = ft_strchr(tp, '/')) != NULL)
		if (need_glob_str(tp + 1))
		{
			after = trace_road(&argv, tp++, &ret, i);
			ft_strdel(&after);
		}
		else
			tp++;
	ft_strdel(&temp3);
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
	int			i;
	char		*temp;
	size_t		len;

	temp = NULL;
	if (!argv)
		return (NULL);
	len = ft_strstrlen(argv);
	while ((i = need_glob(argv)) != -1)
	{
		temp = ft_strdup(argv[i]);
		argv = resolve_glob(argv, i, 1);
		if (!argv || ft_strstrlen(argv) < len)
		{
			if (argv)
				ft_strstrfree(argv);
			ft_triplestr("42sh: no matches found: ", temp, "\n");
			ft_strdel(&temp);
			return (NULL);
		}
		ft_strdel(&temp);
	}
	return (argv);
}
