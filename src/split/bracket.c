/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 11:59:11 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/08 14:59:28 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

static char	**replace_bracket(char **argv, int i, int start, int stop)
{
	char	*temp;
	char	*temp2;
	char	**temp3;
	int		y;

	y = 0;
	temp = ft_strndup(argv[i] + start + 1, stop - start - 1);
	temp3 = ft_strsplit(temp, ',');
	free(temp);
	while (temp3[y])
	{
		temp = ft_strndup(argv[i], start);
		temp2 = ft_strjoin(temp, temp3[y]);
		free(temp3[y]);
		temp3[y] = ft_strjoin(temp2, argv[i] + stop + 1);
		free(temp);
		free(temp2);
		y++;
	}
	argv = ft_strstrdelone(i, argv);
	argv = ft_strstrjoin(argv, temp3);
	return (argv);
}

int			find_place(int *start, int *stop, char *argv)
{
	int i;
	int	open;
	int close;

	i = ft_strlen(argv) + 1;
	while (--i >= 0)
		if (argv[i] == ',' && is_reachable(argv, i))
		{
			close = i;
			open = i;
			while (open != -1 && argv[open] != '{')
				open--;
			while (argv[close] && argv[close] != '}')
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
		if (find_place(&start, &stop, argv[i]) > 0)
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
