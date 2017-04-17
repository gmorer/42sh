/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtab.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:27:48 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/03 18:27:49 by rvievill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTAB_H
# define HASHTAB_H

# define TABLE_LEN 256

# include <dirent.h>
# include "split.h"

typedef struct		s_data
{
	char			*name;
	char			*full_path;
}					t_data;

typedef struct		s_binary
{
	t_data			*data;
	struct s_binary *next;
}					t_binary;

void				add_hash_to_tab(char *binary, char *path);
int					ft_free_hash_tab(void);
t_binary			**ft_init_hash_table(void);
char				*give_path(char *bin, t_binary **table);
int					ft_hash_algo(char *str);

#endif
