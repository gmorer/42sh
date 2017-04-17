/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:35 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/16 10:31:46 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

static char	**split_bracket(char *argv)
{
	char	**rslt;
	size_t	i;
	size_t	start;
	char	*temp;

	rslt = NULL;
	i = 0;
	start = 0;
	while (argv[i])
	{
		if (argv[i] == ',' && is_reachable(argv, i))
		{
			temp = ft_strndup(argv + start, i - start);
			rslt = ft_strstradd(temp, rslt);
			start = i + 1;
		}
		i++;
	}
	temp = ft_strndup(argv + start, i - start);
	rslt = ft_strstradd(temp, rslt);
	return (rslt);
}

static char	**replace_bracket(char **argv, int i, int start, int stop)
{
	char	*temp[2];
	char	**temp3;
	int		y;

	y = 0;
	temp[0] = ft_strndup(argv[i] + start + 1, stop - start - 1);
	temp3 = split_bracket(temp[0]);
	ft_strdel(&temp[0]);
	while (temp3[y])
	{
		if (temp3[y][0] == '\0')
			free(temp3[y]);
		if (temp3[y][0] == '\0')
			temp3[y] = ft_strdup("\"\"");
		temp[0] = ft_strndup(argv[i], start);
		temp[1] = ft_strjoin(temp[0], temp3[y]);
		free(temp3[y]);
		temp3[y] = ft_strjoin(temp[1], argv[i] + stop + 1);
		ft_strdel(&temp[0]);
		ft_strdel(&temp[1]);
		y++;
	}
	argv = ft_strstrdelone(i, argv);
	argv = ft_strstrjoin(argv, temp3);
	return (argv);
}

static int	find_place(int *start, int *stop, char *argv, int i)
{
	int	open;
	int close;

	while (--i >= 0)
		if (argv[i] == ',' && is_reachable(argv, i))
		{
			close = i;
			open = i;
			while (open != -1 && argv[open] != '{' &&
					is_reachable(argv, open))
				open--;
			while (argv[close] && argv[close] != '}' &&
					is_reachable(argv, close))
				close++;
			if (open != -1 && argv[close])
			{
				*start = open;
				return ((*stop = close) ? i : i);
			}
			if (open == -1 && argv[close])
				ft_putendl("zsh: parse error near `}'");
			if (open == -1 && argv[close])
				return (-1);
		}
	return (0);
}

char		**resolve_bracket(char **argv)
{
	int	start;
	int	stop;
	int	i;
	int	test;

	i = 0;
	test = 0;
	if (!argv)
		return (NULL);
	while (argv[i])
	{
		if (find_place(&start, &stop, argv[i], ft_strlen(argv[i] + 1)) > 0)
		{
			test++;
			argv = replace_bracket(argv, i, start, stop);
		}
		i++;
		if (!argv[i] && test != 0)
		{
			test = 0;
			i = 0;
		}
	}
	return (argv);
}
