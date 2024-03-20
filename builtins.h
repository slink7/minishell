/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:45:32 by scambier          #+#    #+#             */
/*   Updated: 2024/03/20 23:58:33 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "env.h"

int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_pwd(int argc, char **argv, t_env *env);
int	builtin_exit(int argc, char **argv, t_env *envp);

#endif