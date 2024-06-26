/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/04/05 16:33:55 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "libft.h"
#include "header.h"

static int	word_split(t_command *dst, char *str)
{
	int	k;

	dst->cmd = ft_splitf(str, s);
	if (ft_strarrlen(dst->cmd) == 0)
		return (0);
	k = -1;
	while (dst->cmd[++k])
		unescape(dst->cmd[k]);
	return (1);
}

int	parse(t_command **out, char **line, t_env *env)
{
	int			k;
	char		**commands;

	expand_variables(line, env);
	escape_quoted(*line);
	commands = ft_split(*line, '|');
	*out = ft_calloc(ft_strarrlen(commands) + 1, sizeof(t_command));
	if (!*out)
		return (0);
	k = -1;
	while (commands[++k])
	{
		(*out)[k].fd_in = 0;
		(*out)[k].fd_out = 1;
		if (!set_command_from_str((*out) + k, commands[k])
			|| !word_split((*out) + k, commands[k]))
		{
			ft_strarrfree(commands);
			return (0);
		}
	}
	ft_strarrfree(commands);
	return (1);
}

int	interpret(char **line, t_env *env)
{
	t_command	*cmds;
	int			k;

	if (parse(&cmds, line, env))
	{
		k = -1;
		while (cmds[++k].cmd)
			;
		exe_piped_commands(k, cmds, env);
	}
	k = -1;
	while (cmds[++k].cmd)
		ft_strarrfree(cmds[k].cmd);
	free(cmds);
	return (1);
}

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_printf_fd(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;

	(void) argc;
	(void) argv;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	env_init(&env, envp);
	while (ft_strncmp(env.last_status, "255", 4) != 0)
	{
		line = readline("\e[22;34mminishell>\e[0m");
		if (!line)
			break ;
		if (ft_strchrf(line, s, 1))
		{
			add_history(line);
			interpret(&line, &env);
		}
		free(line);
	}
	env_deinit(&env);
	printf("Exiting minishell normally... Bye!\n");
	return (0);
}
