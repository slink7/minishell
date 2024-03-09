/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:31:37 by scambier          #+#    #+#             */
/*   Updated: 2024/03/08 18:43:38 by scambier         ###   ########.fr       */
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
	if (*str == 0)
		return (EMPTY);
	if (*str == '\'')
		return (SINGLE_QUOTE);
	else if (*str == '\"')
		return (DOUBLE_QUOTE);
	else if (*str == '(')
		return (PARENTHESIS);
	else if (*str == '$')
		return (RD_VARIABLE);
	else if (*str == '|')
		return (PIPE);
	else if (!ft_strncmp(str, "<<", 2))
		return (RD_H_REDIRECT);
	else if (*str == '<')
		return (RD_REDIRECT);
	else if (!ft_strncmp(str, ">>", 2))
		return (WR_A_REDIRECT);
	else if (*str == '>')
		return (WR_REDIRECT);
	else if (ft_strchr(str, '='))
		return (WR_VARIABLE);
	return (VALUE);
}

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
	else if (line[index] == '\"')
		index += ft_strchri(line + index + 1, '\"') + 2;
	else if (line[index] == '\'')
		index += ft_strchri(line + index + 1, '\'') + 2;
	else
		while (line[index] && !ft_strchr(" \'\"<>", line[index]))
			index++;
	temp = ft_substr(line, start, index - start);
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
		ft_printf_fd(1, tok->str);
		line += ret;
	}
	return (out);
}

char	*eval_tok(t_token *tok)
{
	if (tok->type == DOUBLE_QUOTE)
		return (ft_substr(tok->str, 1, ft_strlen(tok->str) - 2));
	else if (tok->type == SINGLE_QUOTE)
		return (ft_substr(tok->str, 1, ft_strlen(tok->str) - 2));
	else if (tok->type == VALUE)
		return (ft_strdup(tok->str));
	ft_printf_fd(2, "Error : ")
	return (0);
}

t_token	*tok_refine(t_list **tok)
{
	t_token	*out;
	t_token	*t;

	if (!*tok)
		return (0);
	t = (t_token*)(*tok)->content;
	if (t->type >= RD_REDIRECT && t->type <= WR_A_REDIRECT)
	{
		if (!(*tok)->next || ((t_token*)(*tok)->next->content)->type == EMPTY)
		{
			ft_printf_fd(2, "Error: token \"%s\" needs following token\n", t->str);
			return (0);
		}
		out = new_token(eval_tok((*tok)->next->content), t->type);
		*tok = (*tok)->next->next;
	}
	else if (t->type >= VALUE && t->type <= DOUBLE_QUOTE)
	{
		out = new_token(eval_tok((*tok)->content), VALUE);
		*tok = (*tok)->next;
	}
	else
		out = 0;
	return (out);
}

t_list	*toks_refine(t_list *toks)
{
	t_list	*out;
	t_token	*temp;

	out = 0;
	temp = tok_refine(&toks);
	while (temp)
	{
		ft_lstadd_back(&out, ft_lstnew(temp));
		temp = tok_refine(&toks);
	}
	return (out);
}