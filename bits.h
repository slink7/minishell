/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:52:12 by scambier          #+#    #+#             */
/*   Updated: 2024/02/03 03:04:37 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITS_H
# define BITS_H

int		get_bit(int	*src, int b);
void	set_bit(int *src, int b, int v);
void	invert_bit(int *src, int b);

#endif