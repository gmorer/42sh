/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 09:58:59 by gmorer            #+#    #+#             */
/*   Updated: 2016/12/07 12:04:19 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_isin(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		folder(char **str, char ***env, t_shell *shell)
{
	if (access(str[0], F_OK) == -1)
	{
		ft_putstr("minishell: no such file or directory: ");
		ft_putendl(str[0]);
		return (1);
	}
	if (access(str[0], X_OK) == -1)
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl("str[0]");
		return (1);
	}
	return (ft_exec(str[0], str, env, shell));
}

int				ft_redirect(char **str, char ***env, t_binary ***table, t_shell *shell)
{
	char	*bin;
	int		result;
	char	*temp;

	temp = NULL;
	bin = NULL;
	if (ft_isin(str[0], '/'))
	{
		result = folder(str, env, shell);
		return (result);
	}
	if ((result = redirectfunction_builtin(str, env, table)) != -1)
		return (result);
	bin = ft_give_path(str[0], *table, *env);
	if (bin)
	{
		result = ft_exec(bin, str, env, shell);
		free(bin);
		return (result);
	}
	else if ((bin = toexec(*env, str[0])) != NULL)
	{
		result = ft_exec(bin, str, env, shell);
		temp = ft_strsub(bin, 0, ft_strlen(bin) - ft_strlen(str[0]) - 1);
		ft_putendl(temp);
		ft_putendl(str[0]);
		*table = ft_add_hash_to_tab(str[0], temp, *table, *env);
		free(temp);
		return (result);
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(str[0]);
	return (127);
}
