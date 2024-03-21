/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:45:32 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 17:49:11 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_pwd(int argc, char **argv, t_env *env);
int	builtin_exit(int argc, char **argv, t_env *envp);
int	builtin_env(int argc, char **argv, t_env *env);
int	builtin_set(int argc, char **argv, t_env *env);
int	builtin_unset(int argc, char **argv, t_env *env);
int	builtin_export(int argc, char **argv, t_env *env);

int	(*fetch_builtin(char *cmd))(int argc, char **argv, t_env *env);

#endif