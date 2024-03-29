/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:35 by scambier          #+#    #+#             */
/*   Updated: 2024/03/18 17:28:57 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	unescape(char *str)
{
	while (*str)
	{
		if (*str < 0)
			*str += 128;
		str++;
	}
}

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

void	strend(char *str)
{
	static char	c = 0;
	char		temp;

	temp = c;
	c = *str;
	*str = temp;
}
