/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvievill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 18:28:10 by rvievill          #+#    #+#             */
/*   Updated: 2017/04/10 20:10:31 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

# include <dirent.h>
# include <string.h>
# include "libft.h"

char	**glob_get_files(char *previous, char *matchvar, char *after, int *i);
int		need_glob_str(char *str);
int		get_pass(char ***argv, int i, char **tp, char **temp3);
char	*trace_road(char ***argv, char *tp, int *ret, int i);
int		is_reachable(char *str, int i);
int		is_not_quote(char *str, int i);
char	**resolve_bracket(char **str);
char	**argvsplit(char *str, char c);
char	**ft_strstradd(char *str, char **table);
int		match(char *s1, char *s2);
char	*charadd(char *str, char c);
char	**glob_result(char **argv);
char	*ft_quote_add(char *av);
char	*ft_quote(char *av);
char	*argvtest(char *str);
char	**argvclean(char **argv);
char	*rm_bs(char *str);

#endif
