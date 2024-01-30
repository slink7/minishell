/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/01/30 13:21:29 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

#include "libft.h"

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

int	interpret(char *line)
{
	char	**tokens;
	int		k;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	k = -1;
	while (tokens[++k])
		ft_printf_fd(1, "%s\n", tokens[k]);
	ft_strarrfree(tokens);
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
		interpret(line);
		free(line);
	}	
	return (0);
}
