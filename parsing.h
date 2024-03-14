/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:52:38 by scambier          #+#    #+#             */
/*   Updated: 2024/03/13 19:00:37 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"

void	unescape(char *str);
void	strnesc(char *str, int len);
void	escape_quoted(char *str);
void	expand_variables(char **str, t_bst *env);

#endif