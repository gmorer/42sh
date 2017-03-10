/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <gmorer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 18:10:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/03/07 12:54:32 by lvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

# include <dirent.h>
# include <string.h>
# include "libft.h"

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

#endif
