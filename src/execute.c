/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:08:05 by scambier          #+#    #+#             */
/*   Updated: 2024/03/27 13:40:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#include "libft.h"
#include "header.h"

int	append_value(char **argv, t_env *env)
{
	char	*value;

	value = ft_strchr(argv[0], '=') + 1;

	*ft_strchr(argv[0], '+') = '\0';
	env_var_append(argv[0], value, env);
	return (0);
}

int	set_value(char **argv, t_env *env)
{
	char	*value;

	value = ft_strchr(argv[0], '=') + 1;

	*ft_strchr(argv[0], '=') = '\0';
	env_var_set(argv[0], value, env);
	return (0);
}

int	change_value(char **argv, t_env *env)
{
	if (*(ft_strchr(argv[0], '=') - 1) == '+')
		return (append_value(argv, env));
	else
		return (set_value(argv, env) == 1);
}

int	execve_wrap(char *path, char **argv, char **envp)
{
	int	pid;
	int	out;

	pid = fork();
	if (pid == -1)
		return (perror2(1, "minishell"));
	else if (pid == 0)
	{
		execve(path, argv, envp);
		perror("minishell: execve");
		exit(1);
	}
	if (waitpid(pid, &out, 0) == -1)
		return (perror2(1, "minishell: waitpid"));
	return (out);
}

static int	cmd_exec(char **arr_cmd, t_env *env)
{
	int		(*builtin)(int, char**, t_env*);
	char	**paths;
	char	*exe_path;
	int		status;

	builtin = fetch_builtin(arr_cmd[0]);
	if (builtin)
		return (builtin(ft_strarrlen(arr_cmd), arr_cmd, env));
	if (ft_strchr(arr_cmd[0], '='))
	{
		if (change_value(arr_cmd, env) == 1)
			return (1);
		return (0);
	}
	paths = ft_split(ft_bst_getvar(env->envp, "PATH"), ':');
	exe_path = find_executable(paths, arr_cmd[0]);
	ft_strarrfree(paths);
	if (!exe_path)
	{
		ft_printf_fd(2, "minishell: Command '%s' not found\n", arr_cmd[0]);
		return (1);
	}
	status = execve_wrap(exe_path, arr_cmd, env->exp);
	free(exe_path);
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

    if (cmdc < 1 || !cmds)
		return (0);
	if (cmdc == 1)
		return (execute_command(cmds, env));
	if (pipe(fd_pipe))
		return (perror2(1, "minishell: pipe"));
	if (cmds[0].fd_out == 1)
		cmds[0].fd_out = fd_pipe[1];
	if (cmds[1].fd_in == 0)
		cmds[1].fd_in = fd_pipe[0];
	pid = fork();
	if (pid == -1)
		return (perror2(1, "minishell: fork"));
	else if (pid == 0 && (close(fd_pipe[0]) || 1))
		exit(execute_command(cmds, env));
	close(fd_pipe[1]);
	return (exe_pipe_rec(cmdc - 1, cmds + 1, env));
}

int	execute_piped_commands(int cmdc, t_command *cmds, t_env *env)
{
	int	out;

	export_env(env);
	out = exe_pipe_rec(cmdc, cmds, env);
	env->last_status = out;
	printf("Complete cmd exited with : %d\n", out);
	return (out);
}

