/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:08:05 by scambier          #+#    #+#             */
/*   Updated: 2024/03/17 17:51:30 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "t_command.h"

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

int	cmd_exec(char **arr_cmd, char **envp)
{
	char	**paths;
	char	*cmd;

	paths = ft_split(find_path(envp), ':');
	cmd = get_cmd(paths, arr_cmd[0]);
	if (!cmd)
		return (ft_strarrfree(paths));
	ft_strarrfree(paths);
	return (execve(cmd, arr_cmd, envp));
}

#include <sys/wait.h>

int    execute_command(t_command *cmd, char **envp)
{
    int	out;

	dup2(cmd->fd_out, 1);
	dup2(cmd->fd_in, 0);
	out = cmd_exec(cmd->cmd, envp);
	close(cmd->fd_in);
	close(cmd->fd_out);
    return (out);
}

static int    exe_pipe_rec(int cmdc, t_command *cmds, char **envp)
{
    int	pid;
    int	fd_pipe[2];
	int	status;

    if (cmdc < 1 || !cmds)
		return ;
	if (cmdc == 1)
	{
		execute_command(cmds, envp);
		return ;
	}
	status = 0;
	if (pipe(fd_pipe))
	{
		perror("minishell: pipe");
		return ;
	}

	if (cmds[0].fd_out == 1)
		cmds[0].fd_out = fd_pipe[1];
	if (cmds[1].fd_in == 0)
		cmds[1].fd_in = fd_pipe[0];
	
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return ;
	}
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		status = execute_command(cmds, envp);
		perror("minishell: execve");
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status)
			printf("Status:%d\n", status);
		close(fd_pipe[1]);
		exe_pipe_rec(cmdc - 1, cmds + 1, envp);
	}
	return (status);
}

int	execute_piped_commands(int cmdc, t_command *cmds, char **envp)
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
	{
		exe_pipe_rec(cmdc, cmds, envp);
		exit(0);
	}
	else if (waitpid(pid, &out, 0) != pid)
	{
		perror("minishell: waitpid");
		return (0);
	}
	return (out);
}
