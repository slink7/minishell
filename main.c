/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/01/30 18:59:05 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

#include "libft.h"
#include "t_array.h"

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

//"[^"]*"
//'[^']*'
//[^|]+
//

int	get_bit(int	*src, int b)
{
	return (*src & (1 << b)) >> b;
}

void	set_bit(int *src, int b, int v)
{
	*src = (*src & ~(1 << b)) | (v << b);
}

void	invert_bit(int *src, int b)
{
	set_bit(src, b, !get_bit(src, b));
}

t_array	*get_pipes(char *line)
{
	int		k;
	int		is_in_quote;
	int		*pipes;
	int		pipe_k;
	t_array	*out;

	k = -1;
	is_in_quote = 0;
	pipes = ft_calloc(ft_strlen(line), sizeof(int));
	pipe_k = 0;
	while (line[++k])
	{
		if (!get_bit(&is_in_quote, 1) && line[k] == '\"')
			invert_bit(&is_in_quote, 0);
		if (!get_bit(&is_in_quote, 0) && line[k] == '\'')
			invert_bit(&is_in_quote, 1);
		if (!get_bit(&is_in_quote, 1) && !get_bit(&is_in_quote, 0) && line[k] == '|')
			pipes[pipe_k++] = k;
	}
	out = new_array(pipe_k);
	ft_memcpy(out->content, pipes, out->len * sizeof(int));
	return (out);
}

char	**moise(char *line, t_array *pos)
{
	char	**out;
	int		k;
	
	out = ft_calloc(pos->len + 2, sizeof(char *));
	if (!pos->len)
	{
		*out = ft_strdup(line);
		return (out);
	}
	k = 0;
	out[k] = ft_substr(line, 0, pos->content[k]);
	while (++k < pos->len + 1)
		out[k] = ft_substr(line, pos->content[k - 1] + 1, pos->content[k] - pos->content[k - 1] - 1);
	out[k] = ft_substr(line, pos->content[k], ft_strlen(line));
	return (out);
}

int	interpret(char *line)
{
	t_array *pipes;
	char	**sep;

	pipes = get_pipes(line);
	sep = moise(line, pipes);
	int l = -1;
	while (++l < pipes->len + 1)
		printf("[%s]\n", sep[l]);
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
