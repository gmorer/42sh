/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_advanced.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <acottier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 16:07:32 by acottier          #+#    #+#             */
/*   Updated: 2017/03/02 14:35:23 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static	void	command_display(t_input *lst, t_env *env, int null)
{
	int		i;
	char	*entry_swap;
	char	*content_swap;

	i = null + 1;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '=') != 0)
		{
			entry_swap = ft_strdupchr(lst->args[i], '=');
			if ((content_swap = get_env_content(entry_swap, env)) == NULL
					|| null == 1)
				ft_putendl(lst->args[i]);
			if (content_swap)
				free(content_swap);
			free(entry_swap);
		}
		i++;
	}
}

static	int		display(char **env, t_input *lst, int null)
{
	char	*content;
	t_env	*cursor;
	int		i;

	i = 0;
	cursor = env;
	while (env[i])
	{
		ft_putendl(env[i++]);
	}
	command_display(lst, env, null);
	return (0);
}

static	int		env_command(t_env *env, t_input *lst, int command, int null)
{
	char	**swap;

	swap = ft_tabdup(lst->args + command);
	ft_freetab(lst->args);
	lst->args = ft_tabdup(swap);
	ft_freetab(swap);
	free(lst->command);
	lst->command = ft_strdup(lst->args[0]);
	return (do_link(lst, &env, NULL, null));
}

int				env_advanced(char **env, char **argv, int null, char *start)
{
	int	command;
	int	i;

	i = null + 1;
	command = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], '=') == NULL
				&& ft_strcmp(argv[i], "env") != 0)
		{
			command = i;
			break ;
		}
		i++;
	}
	if (command == 0)
		return (display(env, lst, null));
	else if (argv[1] && ft_strcmp(argv[1], "-i") == 0)
		return (null_env(lst, start, env));
	else
		return (env_command(env, lst, command, null));
}
