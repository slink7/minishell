/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:54:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/10 00:47:59 by scambier         ###   ########.fr       */
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

int isws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\0');
}

char	*get_next_word(char *str)
{
	int	k;
	int	start;

	start = 0;
	k = 0;
	while (str[k++])
	{
		if (!start && isws(str[k - 1]) && !isws(str[k]))
			start = k;
		else if (!isws(str[k - 1]) && isws(str[k]))
			return (ft_substr(str, start, k - start));
	}
	return (0);
}

#define FLAG_IN O_CREAT | O_RDONLY
#define FLAG_OUT O_CREAT | O_WRONLY
#define FLAG_OUT_APPEND O_CREAT | O_WRONLY | O_APPEND

void	parse_cmd_in(char *str, t_command *cmd)
{
	char	*start;
	char	*temp;

	start = ft_strchr(str, '<');
	while (start)
	{
		temp = get_next_word(start + 1);
		cmd_setstream(&cmd->fd_in, temp, FLAG_IN, 0777);
		start = ft_strchr(start + 1, '<');
	}
}

void	parse_cmd_out(char *str, t_command *cmd)
{
	static int	flags[] = {FLAG_OUT_APPEND, FLAG_OUT};
	char		*start;
	char		*temp;
	int			append_mode;

	start = ft_strchr(str, '>');
	while (start)
	{
		append_mode = (start[1] == '>');
		temp = get_next_word(start + 1 + append_mode);
		cmd_setstream(&cmd->fd_in, temp, flags[append_mode], 0644);
		start = ft_strchr(start + 1 + append_mode, '>');
	}
}

void	get_command(t_command *out, char *str)
{
	t_list	*toks;

	if (!out)
		return ;
	out->fd_in = 0;
	out->fd_out = 1;
	out->cmd = 0;
	ft_printf_fd(1, "\nTokenising\n");
	toks = tokenise(str);
	ft_printf_fd(1, "\nCommand : \"%s\"\n\tRaw :\n", str);
	print_token_list(toks);
	t_list *e = toks_refine(toks);
	ft_printf_fd(1, "\tRefined :\n");
	print_token_list(e);
}

int	interpret(char *line)
{
	char		**raw_cmds;
	int			len;
	t_command	*cmds;

	raw_cmds = ft_split(line, '|');
	len = ft_strarrlen(raw_cmds);
	cmds = ft_calloc(len, sizeof(t_command));
	for (int k = 0; k < len; k++)
		get_command(cmds + k, raw_cmds[k]);
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
