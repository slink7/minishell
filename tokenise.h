/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:32:16 by scambier          #+#    #+#             */
/*   Updated: 2024/03/13 19:26:47 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_H
# define TOKENISE_H

# include "libft.h"

typedef enum e_token_type
{
	EMPTY,
	VALUE,
	PARENTHESIS,
	RD_REDIRECT,
	RD_H_REDIRECT,
	WR_REDIRECT,
	WR_A_REDIRECT,
}	t_token_type;

typedef struct s_token
{
	char				*str;
	enum e_token_type	type;
}	t_token;

t_token	*new_token(char	*str, enum e_token_type type);
void	free_token(void	*token);
t_list	*tokenise(char *line);
void	toks_refine(t_list **toks);

#endif