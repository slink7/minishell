/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:32:16 by scambier          #+#    #+#             */
/*   Updated: 2024/02/05 15:36:33 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_H
# define TOKENISE_H

# include "libft.h"

typedef struct s_token
{
	char	*str;
}	t_token;

t_token	*new_token(char	*str);
void	free_token(void	*token);
t_list	*tokenise(char *line);

#endif