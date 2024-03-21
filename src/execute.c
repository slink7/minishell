/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:08:05 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 01:31:36 by scambier         ###   ########.fr       */
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

static int	cmd_exec(char **arr_cmd, t_env *env)
{
	int		(*builtin)(int, char**, t_env*);
	char	**paths;
	char	*cmd;
	int		out;

	builtin = fetch_builtin(arr_cmd[0]);
	if (builtin)
	{
		printf("\e[0;32mBuiltin:\n");
		out = builtin(ft_strarrlen(arr_cmd), arr_cmd, env);
		printf("\e[0m");
		exit(out);
	}
	export_env(env);
	paths = ft_split(find_path(env->export), ':');
	cmd = get_cmd(paths, arr_cmd[0]);
	ft_strarrfree(paths);
	if (!cmd)
		exit(1);
	return (execve(cmd, arr_cmd, env->export));
}

int    execute_command(t_command *cmd, t_env *env)
{
    int	out;

	dup2(cmd->fd_out, 1);
	dup2(cmd->fd_in, 0);
	out = cmd_exec(cmd->cmd, env);
	close(cmd->fd_in);
	close(cmd->fd_out);
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
		perror("minishell: execve");
		exit(status);
	}
	else
	{
		close(fd_pipe[1]);
		exe_pipe_rec(cmdc - 1, cmds + 1, env);
	}
	return (status);
}

int	execute_piped_commands(int cmdc, t_command *cmds, t_env *env)
{
	int	pid;
	int	out;

	out = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (0);
	}
	else if (pid == 0)
		exit(exe_pipe_rec(cmdc, cmds, env));
	else if (waitpid(pid, &out, 0) != pid)
	{
		perror("minishell: waitpid");
		return (0);
	}
	return (out);
}
