/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/13 20:07:26 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//#include <stdio.h>

#include "libft.h"
#include "tokenise.h"
#include "t_command.h"
#include "parsing.h"

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
	ft_printf_fd(1, "(%X)[%s]\n", ((t_token *)tokens->content)->type, ((t_token *)tokens->content)->str);
	print_token_list(tokens->next);
}

void	cmd_setstream(int *fd, char *file, int flags, int perms)
{
	if (!fd)
		return ;
	if (*fd != 0 && *fd != 1 && *fd != 2)
		close(*fd);
	*fd = open(file, flags, perms);
}

int	set_command(t_command *cmd, char *str)
{
	t_list	*toks;

	toks = tokenise(str);
	toks_refine(&toks);
	print_token_list(toks);
	(void) cmd;
	return (1);
}

t_command	*parse(char **line)
{
	int			k;
	char		**commands;
	t_command	*out;

	expand_variables(line, 0);
	escape_quoted(*line);
	commands = ft_split(*line, '|');
	out = malloc(sizeof(t_command) * ft_strarrlen(commands));
	k = -1;
	while (commands[++k])
	{
		set_command(out + k, commands[k]);
	}
	ft_strarrfree(commands);
	return (out);
}

int	interpret(char **line)
{

	parse(line);
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
		interpret(&line);
		free(line);
	}
	deinit_env(&env);
	return (0);
}
