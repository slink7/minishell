/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:52:38 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 19:36:57 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "env.h"

void	unescape(char *str);
void	strnesc(char *str, int len);
void	strend(char *str);
void	escape_quoted(char *str);
void	expand_variables(char **str, t_env *env);

// exec

int	here_doc(char *marker);

#endif