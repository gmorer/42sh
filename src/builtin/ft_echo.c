/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <rvievill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:10:19 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/14 18:10:35 by bngo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "split.h"
#include "env.h"

void		display_opt_n(char **argv, int i)
{
	char	*tmp;
	char	*res;
	int		j;
	int		k;

	while (argv[i])
	{
		j = 0;
		k = 0;
		tmp = argv[i] ? ft_strdup(argv[i]) : NULL;
		res = ft_strnew(ft_strlen(tmp));
		if (!res)
			return ;
		while (tmp[j])
			if (tmp[j] == '\\' && special_char(tmp, &res, &k, &j))
				;
			else
				res[k++] = tmp[j++];
		ft_putstr(res);
		argv[i] ? ft_putchar(' ') : 0;
		ft_strdel(&tmp);
		ft_strdel(&res);
		i++;
	}
	ft_putchar('\n');
}

void		display_str(char **argv, int i)
{
	while (argv[i])
	{
		ft_putstr(argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

int			ft_echo(char **argv)
{
	int		i;

	i = 1;
	if (argv[i] && ft_strcmp(argv[i], "-n"))
		display_str(argv, i);
	else if (argv[i] && !ft_strcmp(argv[i], "-n"))
		display_opt_n(argv, i + 1);
	else
		ft_putchar('\n');
	return (0);
}
