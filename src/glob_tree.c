/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:22:04 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/20 13:46:42 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		need_glob_str(char *str)
{
	int	test;
	int	i;

	i = 0;
	test = 0;
	while (str[i] && str[i] != '/')
	{
		if ((i > 0 && str[i] == '?' && str[i - 1] != '\\') || (i == 0 && str[i] == '?'))
			return (1);
		if ((i > 0 && str[i] == '*' && str[i - 1] != '\\') || (i == 0 && str[i] == '*'))
			return (1);
		if ((i > 0 && str[i] == '[' && str[i - 1] != '\\') || (i == 0 && str[i] == '['))
			test = 1;
		if (test == 1 && ((i > 0 && str[i] == ']' && str[i - 1] != '\\') || (i == 0 && str[i] == ']')))
			return (1);;
		i++;
	}
	return (0);
}

char	**glob_get_files(char *previous, char *matchvar, char *after)
{
	struct dirent *file;
	DIR		*actualdir;
	char	**result;
	char	*temp;
	char	*temp1;

	result = ft_strstrnew(0);
	if ((actualdir = opendir(previous ? previous : "./")) == NULL)
	{
		ft_strstrfree(result);
		return (NULL);
	}
	while ((file = readdir(actualdir)))
	{
		if (match(file->d_name, matchvar) && file->d_name[0] != '.')
		{
			if (previous && ft_strcmp(previous, "/"))
			{
				temp1 = ft_strjoin("/", file->d_name);
			}
			else
				temp1 = ft_strdup(file->d_name);
			temp = ft_strjoin(previous, temp1);
			free(temp1);
			temp1 = ft_strjoin(temp, after);
			free(temp);
			result = ft_strstradd(temp1, result);
		}
	}
	closedir(actualdir);
	return (result);
}

char	**resolve_glob(char **argv, int i)
{
	char	*previous;
	char	*after;
	char	*match;
	char	*temp;
	char	**temp2;
	char *temp3;

	temp2 = NULL;
	after = NULL;
	temp = ft_strdup(argv[i]);
	temp3 = temp;
	if (need_glob_str(argv[i]))
	{
		if (!ft_strchr(argv[i], '/'))
			match = ft_strdup(argv[i]);
		else
			match = ft_strndup(argv[i], ft_strlen(argv[i]) - ft_strlen(ft_strchr(argv[i], '/')));
		argv = ft_strstrjoin(argv, (temp2 = glob_get_files(NULL, match, ft_strchr(argv[i], '/'))));
		free(match);
	}
	while ((temp = ft_strchr(temp, '/')) != NULL)
	{
		if (need_glob_str(temp + 1))
		{
			previous = ft_strndup(argv[i], ft_strlen(argv[i]) - ft_strlen(temp));
			if (previous && ft_strcmp(previous, "") == 0)
			{
				free(previous);
				previous = ft_strdup("/");
			}
			if (ft_strchr(temp + 1, '/') == NULL)
			{
				match = ft_strdup(temp + 1);
				after = NULL;
			}
			else
			{
				match = ft_strndup(temp + 1, ft_strlen(temp + 1) - ft_strlen(ft_strchr(temp + 1, '/') ));
				after = ft_strdup(ft_strchr(temp + 1, '/'));
			}
			argv = ft_strstrjoin(argv, (temp2 = glob_get_files(previous, match, after)));
			free(match);
			free(previous);
			if (after)
				free(after);
		}
		temp++;
	}
	free(temp3);
	argv = ft_strstrdelone(i, argv);
	return (argv);
}

int		need_glob(char **str)
{
	int	i;
	int	x;

	x = 0;
	while (str[x])
	{
		i = 0;
		while (str[x][i])
		{
			if (i == 0 && (str[x][i] == '?' || str[x][i] == '*' || str[x][i] == '['))
				return (x);
			if (i > 0 && str[x][i -1] != '\\' && (str[x][i] == '?' || str[x][i] == '*' || str[x][i] == '['))
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
	int i;
	while ((i = need_glob(argv)) != -1)
	{
		argv = resolve_glob(argv, i);
	}
	return (argv);
}
