/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:08:05 by scambier          #+#    #+#             */
/*   Updated: 2024/03/25 15:10:29 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "libft.h"
#include "t_command.h"
#include "env.h"
#include "builtins.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (0);
}

int	append_value(char **argv, t_env *env)
{
	char	*value;

	value = ft_strchr(argv[0], '=') + 1;

	*ft_strchr(argv[0], '+') = '\0';
	builtin_append_value(argv[0], value, env);
	return (0);
}
int	set_value(char **argv, t_env *env)
{
	char	*value;

	value = ft_strchr(argv[0], '=') + 1;

	*ft_strchr(argv[0], '=') = '\0';
	builtin_set(argv[0], value, env);
	return (0);
}

int	change_value(char **argv, t_env *env)
{
	if (*(ft_strchr(argv[0], '=') - 1) == '+')
	{
		if (append_value(argv, env) == 1)
			return (1);
	}
	else
	{
		if (set_value(argv, env) == 1)
			return (1);
	}
	return (0);
}

static int	cmd_exec(char **arr_cmd, t_env *env)
{
	int		(*builtin)(int, char**, t_env*);
	char	**paths;
	char	*cmd;
	int		out;
	int		pid;
	int		status;

	builtin = fetch_builtin(arr_cmd[0]);
	if (builtin)
	{
		printf("\e[0;32mBuiltin:\n");
		out = builtin(ft_strarrlen(arr_cmd), arr_cmd, env);
		printf("\e[0m");
		return (out);
	}
	if (ft_strchr(arr_cmd[0], '='))
	{
		if (change_value(arr_cmd, env) == 1)
			return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	} else if (pid == 0) {
		export_env(env);
		paths = ft_split(find_path(env->export), ':');
		cmd = get_cmd(paths, arr_cmd[0]);
		ft_strarrfree(paths);
		if (!cmd)
			exit(1);
		execve(cmd, arr_cmd, env->export);
		perror("minishell: execve");
		exit(1);
	}
	if (waitpid(pid, &status, 0) == -1) {
		perror("minishell: waitpid");
	}
	return (status);
}

int	ifexited(int status)
{
	return ((status & 0x7F) == 0);
}

int	exitstatus(int status)
{
	return ((status & 0xFF00) >> 8);
}

int    execute_command(t_command *cmd, t_env *env)
{
    int	out;
	int	dups[2];


	dups[0] = dup(0);
	dups[1] = dup(1);
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	out = cmd_exec(cmd->cmd, env);
	dup2(dups[0], 0);
	dup2(dups[1], 1);
	printf("Process [%s] exited with status %d\n", cmd->cmd[0], exitstatus(out));
	return (out);
}

static int    exe_pipe_rec(int cmdc, t_command *cmds, t_env *env)
{
    int	pid;
    int	fd_pipe[2];
	int	status;

    if (cmdc < 1 || !cmds)
		return (0);
	if (cmdc == 1)
		return (execute_command(cmds, env));
	status = 0;
	if (pipe(fd_pipe))
	{
		perror("minishell: pipe");
		return (1);
	}

	if (cmds[0].fd_out == 1)
		cmds[0].fd_out = fd_pipe[1];
	if (cmds[1].fd_in == 0)
		cmds[1].fd_in = fd_pipe[0];
	
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		status = execute_command(cmds, env);
		exit(status);
	}
	close(fd_pipe[1]);
	return (exe_pipe_rec(cmdc - 1, cmds + 1, env));
}

int	execute_piped_commands(int cmdc, t_command *cmds, t_env *env)
{
	int	out;

	out = exe_pipe_rec(cmdc, cmds, env);
	env->last_status = out;
	printf("Complete cmd exited with : %d\n", out);
	return (out);
}

