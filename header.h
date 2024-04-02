/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:56:21 by scambier          #+#    #+#             */
/*   Updated: 2024/04/02 15:22:43 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"

# define ERR_FORK "minishell: fork"
# define ERR_PIPE "minishell: pipe"
# define ERR_OPEN "minishell: open"
# define ERR_EXECVE "minishell: execve"
# define ERR_WAITPID "minishell: waitpid"

//===ENV===
typedef struct s_env
{
	t_bst	*envp;
	t_bst	*vars;
	char	**exp;
	char	*last_status;
}	t_env;

int		env_init(t_env *env, char **envp);
int		env_deinit(t_env *env);
void	env_export(t_env *env);
char	*env_var_get(t_env *env, char *name);
int		env_var_append(t_env *env, char *name, char *value);
int		env_var_set(t_env *env, char *name, char *value);
int		env_var_change(t_env *env, char *cmd);

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
void	goto_falling_edge(char **str, int (*sep)(int));
char	*get_next_word(char *str, int (*sep)(int));

//===EXECUTION===
typedef struct s_command {
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_command;
int		here_doc(char *marker);
int		exe_command(t_command *cmd, t_env *env);
int		exe_piped_commands(int cmdc, t_command *cmds, t_env *env);

//===REDIRECTIONS===
int		set_command_from_str(t_command *cmd, char *str);

//===UTILS===
int		perror2(int ret, char *prompt);
int		exitstatus(int status);

//===EXES===
char	*is_executable(char *path, char *file);
char	*find_executable(char **paths, char *file);

//===PREDICATS===
int		w(int c);
int		s(int c);

#endif