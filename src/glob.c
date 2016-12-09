/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 11:47:27 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/09 16:18:28 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** match test with s1 test pass and 
** s2 incomming string:
** * : ok
** ? : ok
** [] : ko
** {} : ko
*/

char	*blocklist(char c1, char c2, char *result)
{
	char temp;

	if (c1 > c2)
	{
		temp = c1;
		c1 = c2;
		c2 = temp;
	}
	while (c1 < c2)
	{
		result = charadd(result, c1);
		c1++;
	}
	return (result);
}

int	block(char *s2, char c, int *len)
{
	int		i;
	char	*result;

	result = NULL;
	i = 1;
	if (s2[i] == '^')
		i++;
	while (s2[i] && s2[i] != ']')
	{
		if (s2[i] == '-' && i >= 2 && s2[i + 1])
			result = blocklist(s2[i - 1], s2[i + 1], result);
		else
			result = charadd(result, s2[i]);
		i++;
	}
	*len = i;
	if (s2[1] == '^' && !ft_isin(result, c))
		return (1);
	else if (s2[1] != '^' && ft_isin(result, c))
		return (1);
	else
		return (0);
}

int	match(char *s1, char *s2)
{
	int		len;

	len = 0;
	if (*s2 == '[' && *s1)
	{
		if (!block(s2, *s1, &len))
			return (0);
		s2 += len + 1;
		s1++;
	}
	if (*s2 == '\0')
		return (*s1 == '\0');
	if (*s2 == '?' && *s1)
	{
		s2++;
		s1++;
	}
	while (*s2 == '*' && *(s2 + 1) == '*')
		s2++;
//	while (*s2 == '*' && *(s2 + 1) == '*')
//		s2++;
	if (*s1 == '\0' && *s2 == '*' )
		return (match(s1, s2 +1));
	if (*s1 == *s2)
		return (match(s1 + 1, s2 + 1));
	if (*s1 != *s2)
		return ((*s2 == '*') ? (match(s1 + 1, s2) || match(s1, s2 + 1)) : 0);
	return (1);
}

int	ft_match(char **argv)
{
	if (ft_strstrlen(argv) != 3)
		return (1);
	ft_putnbr(match(argv[1], argv[2]));
	ft_putchar('\n');
	return (0);
}
