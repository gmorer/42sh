/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:16 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/11 16:50:37 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include "split.h"
#include "env.h"
#include "shell.h"

t_shell		*g_shell;

static char	*tilde(char *str)
{
	char			*rslt;
	char			*temp;
	struct passwd	*pw;

	if ((temp = getenvline("HOME")))
	{
		rslt = ft_strjoin(temp, str + 1);
		ft_strdel(&str);
		ft_strdel(&temp);
		return (rslt);
	}
	pw = getpwuid(getuid());
	if (!pw)
		return (str);
	rslt = ft_strjoin(pw->pw_name, str + 1);
	ft_strdel(&str);
	return (rslt);
}

char		**ft_strstradd(char *str, char **table)
{
	char	**rslt;
	int		i;

	i = 0;
	rslt = ft_strstrnew(ft_strstrlen(table) + 1);
	if (!table)
		table = ft_strstrnew(0);
	while (table[i] != NULL)
	{
		rslt[i] = (table[i]);
		i++;
	}
	rslt[i] = str;
	rslt[i + 1] = NULL;
	free(table);
	return (rslt);
}

char		**argvsplit(char *av, char c)
{
	char	**rslt;
	int		i;
	int		start;

	i = 0;
	ft_bzero(g_shell->quote, 2 * sizeof(int));
	rslt = NULL;
	while (av[i] && ((start = -1)))
	{
		while (av[i] && av[i] == c)
			i++;
		while (av[i] && (av[i] != c ||
					(av[i] == c && !is_reachable(av, i))))
		{
			start = (start == -1 ? i : start);
			i++;
		}
		rslt = (start != -1 ? ft_strstradd(ft_strndup(av + start, i - start),
					rslt) : rslt);
	}
	rslt = resolve_bracket(rslt);
	return (!(rslt = glob_result(rslt)) ? NULL : argvclean(rslt));
}

char		*charadd(char *str, char c)
{
	char	*rslt;
	size_t	i;
	size_t	len;

	i = 0;
	if (str == NULL)
		len = 0;
	else
		len = ft_strlen(str);
	rslt = ft_strnew(len + 1);
	while (i < len)
	{
		rslt[i] = str[i];
		i++;
	}
	ft_strdel(&str);
	rslt[i] = c;
	rslt[i + 1] = '\0';
	return (rslt);
}

char		**argvclean(char **argv)
{
	size_t	i;
	size_t	len;
	size_t	merge;
	char	**rslt;

	merge = 0;
	i = 0;
	len = ft_strstrlen(argv);
	rslt = ft_strstrnew(len);
	while (i < len)
	{
		if (argv[i][0] == '~' && argv[i][1] != '~')
			argv[i] = tilde(argv[i]);
		rslt[i - merge] = ft_strdup(argv[i]);
		i++;
	}
	ft_strstrfree(argv);
	return (rslt);
}
