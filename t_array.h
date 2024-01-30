/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_array.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:41:10 by scambier          #+#    #+#             */
/*   Updated: 2024/01/30 15:52:38 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ARRAY_H
# define T_ARRAY_H

typedef	struct s_array
{
	int	*content;
	int	len;
}	t_array;

t_array	*new_array(int len);
int		free_array(t_array **arr);

#endif