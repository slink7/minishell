/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 01:31:51 by scambier         ###   ########.fr       */
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
#include "t_command.h"
#include "parsing.h"
#include "env.h"

void	cmd_setstream_fd(int *fd, int new_fd)
{
	printf("%d\n", new_fd);
	if (!fd)
		return ;
	if (*fd != 0 && *fd != 1 && *fd != 2)
		close(*fd);
	*fd = new_fd;
}

void	cmd_setstream(int *fd, char *file, int flags, int perms)
{
	int	new_fd;

	if (!file)
		return ;
	new_fd = open(file, flags, perms);
	if (new_fd == -1)
	{
		perror("minishell : open");
		return ;
	}
	cmd_setstream_fd(fd, new_fd);
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
		type = TYPE_IN1;
	temp = ft_strchr(str, '>');
	if (temp && (temp < *out || !*out))
	{
		*out = temp;
		type = TYPE_OUT1;
	}
	temp = ft_strnstr(str, "<<", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = TYPE_IN2;
	}
	temp = ft_strnstr(str, ">>", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = TYPE_OUT2;
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
		if (!file)
		{
			ft_printf_fd(2, "Error : wrong file name");
			return (0);
		}
		unescape(file);
		if (type & TYPE_IN)
		{
			if (type & TYPE_DOUBLE)
				cmd_setstream_fd(&cmd->fd_in, here_doc(file));
			else
				cmd_setstream(&cmd->fd_in, file, O_RDONLY, 0777);
		}
		else if (type & TYPE_OUT)
		{
			if (type & TYPE_DOUBLE)
				cmd_setstream(&cmd->fd_out, file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			else
				cmd_setstream(&cmd->fd_out, file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		cpy = nr + 1 + !!(type & TYPE_DOUBLE);
		goto_falling_edge(&cpy, s);
		ft_strlcpy(nr, cpy + 1, cpy - nr);
		free(file);
		type = next_redir(nr, &nr);
	}
	cmd->cmd = ft_splitf(str, s);
	type = -1;
	while (cmd->cmd[++type])
		unescape(cmd->cmd[type]);
	
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
	}
	ft_strarrfree(commands);
	return (out);
}

int	execute_piped_commands(int cmdc, t_command *cmds, t_env *env);

int	interpret(char **line, t_env *env)
{
	t_command	*cmds;
	int			k;

	cmds = parse(line);
	k = -1;
	while (cmds[++k].cmd)
		;
	execute_piped_commands(k, cmds, env);
	k = -1;
	while (cmds[++k].cmd)
		ft_strarrfree(cmds[k].cmd);
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
void	export(int	argc, char **argv, t_env *env)
{
	if (!argc)
	{
		ft_bst_print(env->envp);
		return ;
	}
	ft_bst_setvar(&env->envp, argv[0], argv[1]);
}



int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	t_env	env;
	char	*line;
	
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	init_env(&env, envp);
	while (1)
	{
		char b[1000];
		sprintf(b, "\e[22;34mminishell(%d)>\e[0m", getpid());
		line = readline(b);
		if (line && *line)
			add_history(line);
		if (!line || !ft_strncmp(line, "exit", 5))
		{
			free(line);
			break ;
		}
		interpret(&line, &env);
		free(line);
	}
	deinit_env(&env);
	return (0);
}
