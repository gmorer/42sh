/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/15 12:57:25 by gmorer            #+#    #+#             */
/*   Updated: 2016/11/08 14:05:33 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_file(char *path)
{
	DIR				*directory;
	int				result;
	struct dirent	*file;
	char			*temp1;
	char			*temp2;

	result = 0;
	if (!(directory = opendir(path)))
		return (0);
	while ((file = readdir(directory)))
	{
		temp1 = ft_strjoin(path, "/");
		if (!ft_isfolder((temp2 = ft_strjoin(temp1, file->d_name))))
			result++;
		free(temp1);
		free(temp2);
	}
	closedir(directory);
	return (result);
}
	

int			ft_count_binary(char **env)
{
	char	*temp1;
	char	**temp2;
	int	i;
	int	result;

	result = 0;
	i = 0;
	if(!(temp1 = getenvline(env, "PATH=")))
		return (result);
	temp2 = ft_strsplit(temp1, ':');
	free(temp1);
	while (temp2[i])
	{
		result += ft_count_file(temp2[i]);
		free(temp2[i]);
		i++;
	}
	free(temp2);
	ft_putstr("binary :");
	ft_putnbr(result);
	ft_putchar('\n');
	return (result);
}

int	ft_show_hash_tab(char **env, t_binary **table)
{
	int		i;
	t_binary	*bin;
	char		*temp;
	int		len;

	if (!table)
		return (0);
	if(!(temp = getenvline(env, "BINARY_LEN=")))
		return (1);
	len = ft_atoi(temp);
	free(temp);
	i = 0;
	while (i < len)
	{
		if ((table[i]) && (table[i]->data))
		{
			bin = table[i];
			while ((bin) && (bin->data))
			{
				ft_putnbr(i);
				ft_putstr("---------");
				ft_putstr(bin->data->name);
				ft_putstr("---------");
				ft_putendl(bin->data->full_path);
				bin = bin->next;
			}
		}
		i++;
	}
	return (0);
}

int	ft_hash_algo(char *str, char **env)
{
	int	i;
	int	result;
	char	*temp;

	i = 0;
	result = 0;
	while (str[i])
	{
		result = str[i++] + result * 10;
	}
	if ((temp = getenvline(env, "BINARY_LEN=")) == NULL)
	{
		ft_putendl("ft_hash_algo error");
		return (-1);
	}
	result = result % ft_atoi(temp);
	free(temp);
	return (ft_abs(result));
}

int	ft_free_hash_tab(char **env, t_binary ***table)
{
	int		i;
	t_binary	*bin;
	t_binary	*bin2;
	char		*temp;
	int		len;

	if(!(temp = getenvline(env, "BINARY_LEN=")))
		return (1);
	len = ft_atoi(temp);
	free(temp);
	if (!len || !*table)
		return (0);
	i = 0;
	while (i <= len)
	{
		bin = (*table)[i];
		if ((bin))
		{
			bin2 = bin;
			if(bin->data)
			{
				while ((bin))
				{
					bin2 = bin;
					bin = bin->next;
					free(bin2->data->name);
					free(bin2->data->full_path);
					free(bin2->data);
					free(bin2);
				}
			}
			else
				free(bin);
		}
		i++;
	}
	free(*table);
	*table = NULL;
	return (0);
}
