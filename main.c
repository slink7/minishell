/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/02/01 16:51:38 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

#include "libft.h"
#include "t_array.h"
#include "bits.h"

//operateurs : < << > >> |

typedef struct s_env
{
	char	*working_directory;
}	t_env;

int	init_env(t_env *env)
{
	env->working_directory = getcwd(0, 0);
	return (1);
}

int	deinit_env(t_env *env)
{
	free(env->working_directory);
	return (1);
}

typedef	struct s_token
{
	char	*str;
}	t_token;

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

t_list	*tokenise(char *line)
{
	t_list	*out;
	int		start;
	int		index;
	int		in_quote;

	out = 0;
	start = 0;
	index = -1;
	in_quote = 0;
	while (line[++index])
	{
		if (index > 0 && !in_quote && (line[index] == '\"' || (line[index] != ' ' && line[index - 1] == ' ') || (line[index] != ' ' && line[index - 1] == '\"')))
		{
			ft_lstadd_back(&out, ft_lstnew(new_token(ft_substr(line, start, index - start))));
			start = index;
			printf("start at : %d (%c)\n", index, line[index]);
		}
		if (line[index] == '\"')
			in_quote = !in_quote;
	}
	if (line[index - 1] != ' ')
		ft_lstadd_back(&out, ft_lstnew(new_token(ft_substr(line, start, index - start))));
	if (in_quote)
		printf("\033[0;31mError unclosed quote (%d|%d|%c)\033[0m\n", get_bit(&in_quote, 0), get_bit(&in_quote, 1), get_bit(&in_quote, 0) ? '\'' : (get_bit(&in_quote, 1) ? '\"' : '?'));
	return (out);
}

//try avec plein de while empillés

/*
if (line[index] == '@')
	printf("@ i:%d len:%ld bits:%d,%d\n", index, ft_strlen(line), get_bit(&in_quote, 0), get_bit(&in_quote, 1));

if (!in_quote && (ft_strchr("\'\"", line[index]) || (line[index] == ' ' && line[index - 1] != ' ')))
{
	ft_lstadd_back(&out, ft_lstnew(new_token(ft_substr(line, start, index - start))));
	start = index;
}
if (ft_strchr("\'\"", line[index]) && !get_bit(&in_quote, line[index] == '\''))
	invert_bit(&in_quote, line[index] == '\"');
*/

/*
if (index > 0 && !in_quote && line[index] != ' ' && line[index - 1] == ' ')
	start = index;
if (!get_bit(&in_quote, 0) && line[index] == '\"')
	invert_bit(&in_quote, 1);
if (!get_bit(&in_quote, 1) && line[index] == '\'')
	invert_bit(&in_quote, 0);
if (index > 0 && !in_quote && (line[index] == ' ' || line[index] == '\"' || !line[index]) && line[index - 1] != ' ')
	ft_lstadd_back(&out, ft_lstnew(new_token(ft_substr(line, start, index - start))));
*/

//"a" bc "d 'e"fh '' ij" k"

void	print_token_list(t_list *tokens)
{
	if (!tokens)
		return ;
	printf("[%s]\n", ((t_token *)tokens->content)->str);
	print_token_list(tokens->next);
}

int	interpret(char *line)
{
	t_list *tokens;
	//char	**sep;
	tokens = 0;
	tokens = tokenise(line);
	printf("Size : %d\n", ft_lstsize(tokens));
	print_token_list(tokens);
	ft_lstclear(&tokens, free_token);
	return (1);
}

int	main(void)
{
	t_env	env;
	char	*line;

	init_env(&env);
	while (1)
	{
		ft_printf_fd(1, "\033[22;34m%s>\033[0m", env.working_directory);
		line = get_next_line(0);
		line[ft_strlen(line) - 1] = 0;
		if (!ft_strncmp(line, "exit", 5))
		{
			free(line);
			break;
		}
		interpret(line);
		free(line);
	}
	get_next_line(-1);
	deinit_env(&env);
	return (0);
}
