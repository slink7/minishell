/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_array.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:41:41 by scambier          #+#    #+#             */
/*   Updated: 2024/01/30 15:56:07 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "t_array.h"
#include "libft.h"

t_array	*new_array(int len)
{
	t_array	*out;

	out = ft_calloc(1, sizeof(t_array));
	if (!out)
		return (0);
	out->len = len;
	out->content = ft_calloc(out->len, sizeof(int));
	return (out);
}

int	free_array(t_array **arr)
{
	free((*arr)->content);
	free(*arr);
	*arr = 0;
	return (1);
}