/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:08:05 by scambier          #+#    #+#             */
/*   Updated: 2024/04/02 13:56:55 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "libft.h"
#include "header.h"

int	execve_wrap(char *path, char **argv, char **envp)
{
	int	pid;
	int	out;

	pid = fork();
	if (pid == -1)
		return (perror2(1, ERR_FORK));
	else if (pid == 0)
	{
		execve(path, argv, envp);
		exit(perror2(1, ERR_EXECVE));
	}
	if (waitpid(pid, &out, 0) == -1)
		return (perror2(1, ERR_WAITPID));
	return (out);
}

static int	exe_executable(char **arr_cmd, t_env *env)
{
	int		(*builtin)(int, char**, t_env*);
	char	*exe_path;
	char	**paths;
	int		status;

	builtin = fetch_builtin(arr_cmd[0]);
	if (builtin)
		return (builtin(ft_strarrlen(arr_cmd), arr_cmd, env));
	if (ft_strchr(arr_cmd[0], '='))
		return (env_var_change(env, arr_cmd[0]) == 1);
	exe_path = ft_bst_getvar(env->envp, "PATH");
	paths = 0;
	if (exe_path)
		paths = ft_split(exe_path, ':');
	exe_path = find_executable(paths, arr_cmd[0]);
	if (paths)
		ft_strarrfree(paths);
	if (!exe_path)
	{
		ft_printf_fd(2, "minishell: Command '%s' not found\n", arr_cmd[0]);
		return (32512);
	}
	status = execve_wrap(exe_path, arr_cmd, env->exp);
	free(exe_path);
	return (status);
}

int	exe_command(t_command *cmd, t_env *env)
{
	int	out;
	int	dups[2];

	dups[0] = dup(0);
	dups[1] = dup(1);
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	out = exe_executable(cmd->cmd, env);
	dup2(dups[0], 0);
	dup2(dups[1], 1);
	return (out);
}

static int	exe_piped_rec(int cmdc, t_command *cmds, t_env *env)
{
	int	pid;
	int	fd_pipe[2];

	if (cmdc < 1 || !cmds)
		return (1);
	if (cmdc == 1)
		return (exe_command(cmds, env));
	if (pipe(fd_pipe))
		return (perror2(1, ERR_PIPE));
	if (cmds[0].fd_out == 1)
		cmds[0].fd_out = fd_pipe[1];
	if (cmds[1].fd_in == 0)
		cmds[1].fd_in = fd_pipe[0];
	pid = fork();
	if (pid == -1)
		return (perror2(1, ERR_FORK));
	else if (pid == 0 && (close(fd_pipe[0]) || 1))
		exit(exe_command(cmds, env));
	close(fd_pipe[1]);
	return (exe_piped_rec(cmdc - 1, cmds + 1, env));
}

int	exe_piped_commands(int cmdc, t_command *cmds, t_env *env)
{
	int	out;

	env_export(env);
	out = exe_piped_rec(cmdc, cmds, env);
	env->last_status = out;
	printf("[%d]", exitstatus(out));
	return (out);
}
