/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:31:37 by scambier          #+#    #+#             */
/*   Updated: 2024/03/13 19:53:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "tokenise.h"
#include "t_command.h"

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

enum e_token_type	get_token_type(char *str)
{
	if (!str || *str == 0)
		return (EMPTY);
	else if (*str == '(')
		return (PARENTHESIS);
	else if (!ft_strncmp(str, "<<", 2))
		return (RD_H_REDIRECT);
	else if (*str == '<')
		return (RD_REDIRECT);
	else if (!ft_strncmp(str, ">>", 2))
		return (WR_A_REDIRECT);
	else if (*str == '>')
		return (WR_REDIRECT);
	return (VALUE);
}

#include "parsing.h"

int	get_next_token(t_token **out, char *line)
{
	int		index;
	int		start;
	char	*temp;

	if (!*line)
	{
		*out = 0;
		return (0);
	}
	index = 0;
	while (line[index] == ' ')
		index++;
	start = index;
	if (line[index] == '<')
		index += 1 + (line[index + 1] == '<');
	else if (line[index] == '>')
		index += 1 + (line[index + 1] == '>');
	else
		while (line[index] && !ft_strchr(" <>", line[index]))
			index++;
	temp = ft_substr(line, start, index - start);
	unescape(temp);
	*out = new_token(temp, get_token_type(temp));
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

#include <stdio.h>

t_token	*tok_refine(t_list **tok)
{
	t_token	*out;
	t_token	*t;

	if (!*tok)
		return (0);
	t = (*tok)->content;
	if (t->type >= RD_REDIRECT && t->type <= WR_A_REDIRECT)
	{
		if (!(*tok)->next || ((t_token*)(*tok)->next->content)->type == EMPTY)
		{
			ft_printf_fd(2, "Error: token \"%s\" needs following token\n", t->str);
			return (0);
		}
		out = new_token(ft_strdup(((t_token*)(*tok)->next->content)->str), t->type);
		*tok = (*tok)->next->next;
	}
	else if (t->type == VALUE)
	{
		out = new_token(ft_strdup(t->str), VALUE);
		*tok = (*tok)->next;
	}
	else
		out = 0;
	return (out);
}

void	toks_refine(t_list **toks)
{
	t_list	*out;
	t_list	*qoizjd;
	t_token	*temp;

	out = 0;
	temp = tok_refine(toks);
	qoizjd = *toks;
	while (temp)
	{
		ft_lstadd_back(&out, ft_lstnew(temp));
		temp = tok_refine(&qoizjd);
	}
	ft_lstclear(toks, free_token);
	*toks = out;
}