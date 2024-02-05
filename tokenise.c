/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:31:37 by scambier          #+#    #+#             */
/*   Updated: 2024/02/05 18:48:46 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenise.h"

t_token	*new_token(char	*str, enum e_token_type type)
{
	t_token	*out;

	out = malloc(sizeof(t_token));
	out->str = str;
	out->type = type;
	return (out);
}

void	free_token(void	*token)
{
	free(((t_token *)token)->str);
	free(token);
}

/*
enum e_token_type
{
	VALUE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PARENTHESIS,
	RD_VARIABLE,
	WR_VARIABLE,
	PIPE,
	RD_REDIRECT,
	RD_A_REDIRECT,
	WR_REDIRECT,
	WR_H_REDIRECT,
};
*/

// enum e_token_type	get_token_type(char *str)
// {
// 	if (*str == 0)
// 		return (EMPTY);
// 	if (*str == '\'')
// 		return (SINGLE_QUOTE);
// 	else if (*str == '\"')
// 		return (DOUBLE_QUOTE);
// 	else if (*str == '(')
// 		return (PARENTHESIS);
// 	else if (*str == '$')
// 		return (RD_VARIABLE);
// 	else if (*str == '|')
// 		return (PIPE);
// 	else if (*str == '<')
// 		if (*(str + 1) == '<')
// 			return (RD_H_REDIRECT)
// 		else
// 			return (RD_REDIRECT);
// 	else if (*str == '>')
// 	else if (ft_strchr(str, '='))
// 		return (WR_VARIABLE);
	
// }

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
