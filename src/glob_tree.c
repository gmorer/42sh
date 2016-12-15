/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:22:04 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/15 17:55:09 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		need_glob_str(char *str)
{
	int	test;
	int	i;

	ft_putstr("enter un ?: ");
	ft_putendl(str);
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

	ft_putstr("you are here with for previous: ");
	ft_putendl(previous);
	result = ft_strstrnew(0);
	if ((actualdir = opendir(previous)) == NULL)
	{
		ft_putstr("no matches found: ");
		ft_putstr(previous);
		ft_putstr(matchvar);
		ft_putstr(after);
		return (NULL);
	}
	while ((file = readdir(actualdir)))
	{
		ft_putstr("match entre ");
		ft_putstr(file->d_name);
		ft_putstr(" et ");
		ft_putendl(matchvar);
		if (match(file->d_name, matchvar) && file->d_name[0] != '.')
		{
			ft_putstr("match for: ");
			ft_putendl(file->d_name);
			temp1 = ft_strjoin("/", file->d_name);
			temp = ft_strjoin(previous, temp1);
			free(temp1);
			ft_putstr("temp: ");
			ft_putendl(temp);
			temp1 = ft_strjoin(temp, after);
			free(temp);
			ft_putendl("test1");
			ft_putstr("temp1 :");
			ft_putendl(temp1);
			ft_putendl("test1.5");
			result = ft_strstradd(temp1, result);
			ft_putendl("test2");
		}
	}
	ft_putendl("return:");
	ft_putmap(result);
	ft_putendl("end return");
	return (result);
}

char	**resolve_glob(char **argv, int i)
{
	char	*previous;
	char	*after;
	char	*match;
	char	*temp;

	temp = argv[i];
	ft_putstr("enter resolve with for globstr: ");
	ft_putendl(temp);
	while ((temp = ft_strchr(temp, '/')) != NULL)
	{
		if (need_glob_str(temp + 1))
		{
			ft_putendl("got it");
			ft_putstr("temp: ");
			ft_putendl(temp);
			ft_putstr("argv: ");
			ft_putmap(argv);
			ft_putendl("test1");
			ft_putnbr(ft_strlen(argv[i]) - ft_strlen(temp));
			ft_putchar('\n');
			previous = ft_strndup(argv[i], ft_strlen(argv[i]) - ft_strlen(temp));
			if (ft_strchr(temp + 1, '/') == NULL)
			{
				ft_putendl("you are tyhe last");
				match = ft_strdup(temp + 1);
				ft_putstr("matchvar: ");
				ft_putendl(match);
				after = NULL;
			}
			else
			{
				match = ft_strndup(temp + 1, ft_strlen(ft_strchr(temp + 1, '/') + 1));
				ft_putstr("matchvar: ");
				ft_putendl(match);
				after = ft_strchr(temp + 1, '/');
			}
			argv = ft_strstrjoin(argv, glob_get_files(previous, match, after));
			argv = ft_strstrdelone(i, argv);
			ft_putendl("///////////////");
			ft_putmap(argv);
			ft_putendl("///////////////");
			//free(previous);
			//free(match);
		}
		else
		{
			ft_putstr("nothing to do with: ");
			ft_putendl(temp);
		}
		temp++;
	}
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
	ft_putendl("enter in foirst while");
	while ((i = need_glob(argv)) != -1)
	{
		//ft_putendl("enter in resolve glob");
		argv = resolve_glob(argv, i);
		//ft_putendl("quitting resolve glob");
	}
	ft_putendl("quiting first while");
	return (argv);
}
