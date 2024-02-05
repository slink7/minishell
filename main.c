/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/02/05 16:17:06 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include <stdio.h>

#include "libft.h"
#include "t_array.h"
#include "tokenise.h"

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

void	print_token_list(t_list *tokens)
{
	if (!tokens)
		return ;
	printf("[%s]\n", ((t_token *)tokens->content)->str);
	print_token_list(tokens->next);
}

int	interpret(char *line)
{
	t_list	*tokens;

	tokens = tokenise(line);
	printf("Size : %d\n", ft_lstsize(tokens));
	print_token_list(tokens);
	ft_lstclear(&tokens, free_token);
	return (1);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	t_env	env;
	char	*line;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_env(&env);
	while (1)
	{
		line = readline("\033[22;34mminishell>\033[0m");
		if (line && *line)
			add_history(line);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			free(line);
			break ;
		}
		interpret(line);
		free(line);
	}
	deinit_env(&env);
	return (0);
}
