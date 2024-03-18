/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_quoted.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:47:16 by scambier          #+#    #+#             */
/*   Updated: 2024/03/18 17:31:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

void	escape_quoted(char *str)
{
	static char	*quotes = "\'\"";
	char		*next;
	int			fk;

	fk = -1;
	while (str[++fk])
	{
		if (ft_strchr(quotes, str[fk]))
		{
			next = ft_strchr(str + fk + 1, str[fk]);
			if (!next)
			{
				ft_printf_fd(2, "Error ! missing quote %c %s\n", str[fk], str + fk + 1);
				return ;
			}
			ft_strlcpy(str + fk, str + fk + 1, ft_strlen(str + fk));
			ft_strlcpy(next - 1, next, ft_strlen(next) + 1);
			strnesc(str + fk, next - str - fk - 1);
			fk = next - str - 2;
		}
	}
}