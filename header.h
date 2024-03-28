/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:56:21 by scambier          #+#    #+#             */
/*   Updated: 2024/03/28 18:11:53 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"

# define ERR_FORK "minishell: fork"
# define ERR_PIPE "minishell: pipe"
# define ERR_EXECVE "minishell: execve"
# define ERR_WAITPID "minishell: waitpid"

//===ENV===
typedef struct s_env
{
	t_bst	*envp;
	t_bst	*vars;
	char	**exp;
	int		last_status;
}	t_env;

int		env_init(t_env *env, char **envp);
int		env_deinit(t_env *env);
void	env_export(t_env *env);
char	*env_get_value(t_env *env, char *name);
int		env_var_append(t_env *env, char *name, char *value);
int		env_var_set(t_env *env, char *name, char *value);
int		env_change_value(t_env *env, char *cmd);

//===BUILTINS===
int		builtin_cd(int argc, char **argv, t_env *env);
int		builtin_pwd(int argc, char **argv, t_env *env);
int		builtin_exit(int argc, char **argv, t_env *envp);
int		builtin_env(int argc, char **argv, t_env *env);
int		builtin_unset(int argc, char **argv, t_env *env);
int		builtin_export(int argc, char **argv, t_env *env);
int		builtin_echo(int argc, char **argv, t_env *env);
int		builtin_niel(int argc, char **argv, t_env *env);

int		(*fetch_builtin(char *cmd))(int argc, char **argv, t_env *env);

//===PARSING===
void	unescape(char *str);
void	strnesc(char *str, int len);
void	strend(char *str);
void	escape_quoted(char *str);
void	expand_variables(char **str, t_env *env);

//===EXECUTION===
typedef struct s_command {
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_command;
int		here_doc(char *marker);
int		exe_command(t_command *cmd, t_env *env);
int		exe_piped_commands(int cmdc, t_command *cmds, t_env *env);

//===UTILS===
int		perror2(int ret, char *prompt);
int		exitstatus(int status);

//===EXES===
char	*is_executable(char *path, char *file);
char	*find_executable(char **paths, char *file);

#endif