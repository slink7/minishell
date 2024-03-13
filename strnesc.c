/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnesc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:35 by scambier          #+#    #+#             */
/*   Updated: 2024/03/13 17:50:44 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	strnesc(char *str, int len)
{
	if (!str || !*str || len < 0)
		return ;
	if (len > 0)
		while (--len >= 0)
			str[len] -= (str[len] >= 0) * 128;
	else
		strnesc(str, ft_strlen(str));
}