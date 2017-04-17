/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvalenti <lvalenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 17:29:16 by lvalenti          #+#    #+#             */
/*   Updated: 2017/04/15 13:14:03 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

static int		ft_inbase(char c, int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '9');
	return ((c >= '0' && c <= '9') || (ft_toupper(c) >= 'A' &&
				ft_toupper(c) <= ('A' + base - 10)));
}

int				ft_atoi_base(const char *str, int str_base)
{
	int		value;
	int		sign;

	value = 0;
	if (str_base <= 1 || str_base > 36)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
			|| *str == '\r' || *str == '\v')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_inbase(*str, str_base))
	{
		if (ft_toupper(*str) - 'A' >= 0)
			value = value * str_base + (ft_toupper(*str) - 'A' + 10);
		else
			value = value * str_base + (*str - '0');
		str++;
	}
	return (value * sign);
}

static int		check_base(char *str)
{
	while (*str)
	{
		if (*str > '7')
			return (0);
		str++;
	}
	return (1);
}

static int		dec_to_oct(char *str, char **res, int *k, int *j)
{
	char		*tmp;
	int			i;
	int			l;
	int			e;

	i = *j + 1;
	l = 3;
	while ((i + l) > (int)ft_strlen(str))
		l--;
	tmp = ft_strsub(str, i + 1, l);
	while (!check_base(tmp))
	{
		ft_strdel(&tmp);
		tmp = ft_strsub(str, i + 1, --l);
	}
	if ((e = ft_atoi_base(tmp, 8)))
		(*res)[(*k)++] = e;
	else
	{
		ft_strdel(&tmp);
		return (0);
	}
	i = ft_strlen(tmp);
	ft_strdel(&tmp);
	return (i);
}

int				special_char(char *str, char **res, int *k, int *i)
{
	int			j;

	j = 0;
	if (str[*i + 1] == 'a' && ++j)
		(*res)[(*k)++] = '\a';
	else if (str[*i + 1] == 'b' && ++j)
		(*res)[(*k)++] = '\b';
	else if (str[*i + 1] == 'c' && ++j)
		(*res)[(*k)++] = 0;
	else if (str[*i + 1] == 'f' && ++j)
		(*res)[(*k)++] = '\f';
	else if (str[*i + 1] == 'n' && ++j)
		(*res)[(*k)++] = '\n';
	else if (str[*i + 1] == 'r' && ++j)
		(*res)[(*k)++] = '\r';
	else if (str[*i + 1] == 't' && ++j)
		(*res)[(*k)++] = '\t';
	else if (str[*i + 1] == 'v' && ++j)
		(*res)[(*k)++] = '\v';
	else if (str[*i + 1] == '\\' && ++j)
		(*res)[(*k)++] = '\\';
	else if (str[*i + 1] == '0' && ++j)
		*i += dec_to_oct(str, res, k, i);
	(*i) += j ? 2 : 0;
	return (j ? 1 : 0);
}
