/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob2ez.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:25:51 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:25:51 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

int		get_pass(char ***argv, int i, char **tp, char **temp3)
{
	char	*match;
	int		ret;

	ret = 1;
	*tp = ft_strdup((*argv)[i]);
	*temp3 = *tp;
	if (need_glob_str((*argv)[i]))
	{
		if (!ft_strchr((*argv)[i], '/'))
			match = ft_strdup((*argv)[i]);
		else
			match = ft_strndup((*argv)[i], ft_strlen((*argv)[i]) -
					ft_strlen(ft_strchr((*argv)[i], '/')));
		*argv = ft_strstrjoin(*argv,
				glob_get_files(NULL, match, ft_strchr((*argv)[i], '/'), &ret));
		ft_strdel(&match);
	}
	return (ret);
}

char	*trace_road(char ***argv, char *tp, int *ret, int i)
{
	char	*match;
	char	*previous;
	char	*after;

	after = NULL;
	previous = ft_strndup((*argv)[i], ft_strlen((*argv)[i]) - ft_strlen(tp));
	if (previous && ft_strcmp(previous, "") == 0)
	{
		ft_strdel(&previous);
		previous = ft_strdup("/");
	}
	match = (!ft_strchr(tp + 1, '/') ? ft_strdup(tp + 1) :
			ft_strndup(tp + 1, ft_strlen(tp + 1) -
				ft_strlen(ft_strchr(tp + 1, '/'))));
	after = (!ft_strchr(tp + 1, '/') ? NULL :
			ft_strdup(ft_strchr(tp + 1, '/')));
	*argv = ft_strstrjoin(*argv,
			glob_get_files(previous, match, after, ret));
	ft_strdel(&match);
	ft_strdel(&previous);
	return (after);
}
