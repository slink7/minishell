/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:52:12 by scambier          #+#    #+#             */
/*   Updated: 2024/01/31 13:52:42 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITS_H
# define BITS_H

int	get_bit(int	*src, int b)
{
	return (*src & (1 << b)) >> b;
}

void	set_bit(int *src, int b, int v)
{
	*src = (*src & ~(1 << b)) | (v << b);
}

void	invert_bit(int *src, int b)
{
	set_bit(src, b, !get_bit(src, b));
}

#endif