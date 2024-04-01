/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:35 by scambier          #+#    #+#             */
/*   Updated: 2024/04/01 14:36:04 by scambier         ###   ########.fr       */
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

void	goto_falling_edge(char **str, int (*sep)(int))
{
	char	*s;
	int		k;

	s = *str;
	k = -1;
	while (s[++k])
		if (!sep(s[k]) && sep(s[k + 1]))
			break ;
	*str = s + k;
}

char	*get_next_word(char *str, int (*sep)(int))
{
	int	k;
	int	start;

	start = 0;
	k = -1;
	while (str[++k])
	{
		if (!start && sep(str[k]) && !sep(str[k + 1]))
			start = k + 1;
		else if (!sep(str[k]) && sep(str[k + 1]))
			return (ft_substr(str, start, k + 1 - start));
	}
	return (0);
}
