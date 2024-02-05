/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:31:37 by scambier          #+#    #+#             */
/*   Updated: 2024/02/05 15:38:00 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenise.h"

t_token	*new_token(char	*str)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->str = str;
	return (out);
}

void	free_token(void	*token)
{
	free(((t_token *)token)->str);
	free(token);
}

int	get_next_token(t_token **out, char *line)
{
	int	index;
	int	start;

	if (!*line)
	{
		*out = 0;
		return (0);
	}
	index = 0;
	while (line[index] == ' ')
		index++;
	start = index;
	if (line[index] == '\"')
		index += ft_strchri(line + index + 1, '\"') + 2;
	else if (line[index] == '\'')
		index += ft_strchri(line + index + 1, '\'') + 2;
	else if (line[index] == '(')
		index += ft_strchri(line + index + 1, ')') + 2;
	else
		while (line[index] && !ft_strchr(" \'\"(", line[index]))
			index++;
	*out = new_token(ft_substr(line, start, index - start));
	return (index);
}

//"a" bc "d 'e"fh '' ij" k"
//"a" b(c "d 'e"fh '') ij" k"

t_list	*tokenise(char *line)
{
	t_list	*out;
	t_token	*tok;
	int		ret;

	out = 0;
	tok = 0;
	while (1)
	{
		ret = get_next_token(&tok, line);
		if (!tok)
			break ;
		ft_lstadd_back(&out, ft_lstnew(tok));
		line += ret;
	}
	return (out);
}
