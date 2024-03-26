/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niel.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:22:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/26 22:06:55 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int    execute_command(t_command *cmd, t_env *env);

int	builtin_niel(int argc, char **argv, t_env *env)
{
	t_command	cmd;

	(void)argc;
	(void)argv;
	(void)env;
	cmd.cmd = (char*[]) {"cat", "niel", 0};
	cmd.fd_in = 0;
	cmd.fd_out = 1;
	return (execute_command(&cmd, env));
}