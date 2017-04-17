/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:43 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/17 14:51:47 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"
#include "env.h"

/*
** match test with s1 test pass and
** s2 incomming string:
** * : ok
** ? : ok
** [] : ok
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

int		block(char *s2, char c, int *len)
{
	int		i;
	char	*result;

	result = NULL;
	i = (s2[1] == '^' ? 2 : 1);
	while (s2[i] && s2[i] != ']')
	{
		if (s2[i] == '-' && i >= 2 && s2[i + 1])
			result = blocklist(s2[i - 1], s2[i + 1], result);
		else
			result = charadd(result, s2[i]);
		i++;
	}
	*len = i;
	if ((s2[1] == '^' && !ft_isin(result, c)) ||
			(s2[1] != '^' && ft_isin(result, c)))
	{
		ft_strdel(&result);
		return (1);
	}
	else
	{
		ft_strdel(&result);
		return (0);
	}
}

int		match(char *s1, char *s2)
{
	int		len;

	len = 0;
	if (*s2 == '[' && *s1 && *(s2 + 1) != ']')
	{
		if (!block(s2, *s1, &len))
			return (0);
		s2 += len + 1;
		s1++;
	}
	if (*s2 == '\0')
		return (*s1 == '\0');
	if (*s2 == '\0')
		return (*s1 == '\0');
	while (*s2 == '*' && *(s2 + 1) == '*')
		s2++;
	if (*s1 == '\0' && *s2 == '*')
		return (match(s1, s2 + 1));
	if (*s1 == *s2 || (*s2 == '?' && *s1))
		return (match(s1 + 1, s2 + 1));
	if (*s1 != *s2)
		return ((*s2 == '*') ? (match(s1 + 1, s2) || match(s1, s2 + 1)) : 0);
	return (1);
}

int		ft_match(char **argv)
{
	char	**temp;
	char	**things_to_free;

	if (ft_strstrlen(argv) != 2)
		return (1);
	temp = ft_strstrdup(argv);
	things_to_free = glob_result(temp);
	ft_strstrfree(things_to_free);
	return (0);
}
