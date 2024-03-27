/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:56:21 by scambier          #+#    #+#             */
/*   Updated: 2024/03/27 14:42:28 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"

//===ENV===
typedef struct s_env
{
	t_bst	*envp;
	t_bst	*vars;
	char	**exp;
	int		last_status;
}	t_env;

int		init_env(t_env *env, char **envp);
int		deinit_env(t_env *env);
void	export_env(t_env *env);
char	*get_value(char *name, t_env *env);

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

int		env_var_append(char *var, char *value, t_env *env);
int		env_var_set(char *var, char *value, t_env *env);

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

//===UTILS===
int		perror2(int ret, char *prompt);

//===EXES===
char	*is_executable(char *path, char *file);
char	*find_executable(char **paths, char *file);

#endif