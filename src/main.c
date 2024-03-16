/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/16 16:56:36 by scambier         ###   ########.fr       */
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
	if (*fd == -1)
		perror("minishell: open");
}

#define TYPE_IN1 1
#define TYPE_OUT1 2
#define TYPE_IN2 4
#define TYPE_OUT2 8

#define TYPE_IN 5
#define TYPE_OUT 10
#define TYPE_SIMPLE 3
#define TYPE_DOUBLE 12

int	next_redir(char *str, char **out)
{
	char	*temp;
	int		type;

	type = 0;
	*out = ft_strchr(str, '<');
	if (*out)
		type = 1;
	temp = ft_strchr(str, '>');
	if (temp && (temp < *out || !*out))
	{
		*out = temp;
		type = 2;
	}
	temp = ft_strnstr(str, "<<", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = 3;
	}
	temp = ft_strnstr(str, ">>", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = 4;
	}
	return (type);
}

int s(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

char	*get_next_word(char *str, int (*sep)(int))
{
	int	k;
	int	start;

	start = 0;
	k = -1;
	while (str[++k])
	{
		if (!start && sep(str[k]) && !sep(str[k + 1]))
			start = k + 1;
		else if (!sep(str[k]) && sep(str[k + 1]))
			return (ft_substr(str, start, k + 1 - start));
	}
	return (0);
}

void	goto_falling_edge(char **str, int (*sep)(int))
{
	char	*s;
	int		k;

	s = *str;
	k = -1;
	while (s[++k])
		if (!sep(s[k]) && sep(s[k + 1]))
			break ;
	*str = s + k;
}

int	set_command(t_command *cmd, char *str)
{
	char	*nr;
	char	*file;
	char	*cpy;
	int		type;

	type = next_redir(str, &nr);
	while (type)
	{
		file = get_next_word(nr + 1 + !!(type & TYPE_DOUBLE), s);
		if (type & TYPE_IN)
			cmd_setstream(&cmd->fd_in, file, O_RDONLY, 0777);
		else if (type & TYPE_OUT)
			cmd_setstream(&cmd->fd_out, file, O_WRONLY, 0644);
		cpy = nr + 1 + !!(type & TYPE_DOUBLE);
		goto_falling_edge(&cpy, s);
		ft_strlcpy(nr, cpy + 1, cpy - nr);
		free(file);
		type = next_redir(nr, &nr);
	}
	cmd->cmd = ft_splitf(str, s);
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
	out = ft_calloc(ft_strarrlen(commands) + 1, sizeof(t_command));
	k = -1;
	while (commands[++k])
	{
		out[k].fd_in = 0;
		out[k].fd_out = 1;
		set_command(out + k, commands[k]);
		// for (int l = 0; out[k].cmd[l]; l++)
		// 	printf("[%s] ", out[k].cmd[l]);
		// printf("\n");
	}
	ft_strarrfree(commands);
	return (out);
}

void    pipe_exe(int cmdc, t_command *cmds, char **envp);

int	interpret(char **line, char **envp)
{
	t_command	*cmds;
	int			k;

	cmds = parse(line);
	k = -1;
	while (cmds[++k].cmd)
		;
	pipe_exe(k, cmds, envp);
	free(cmds);
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

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;

	(void) argc;
	(void) argv;
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
		interpret(&line, envp);
		free(line);
	}
	deinit_env(&env);
	return (0);
}
