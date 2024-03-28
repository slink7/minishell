/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   niel.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:22:28 by scambier          #+#    #+#             */
/*   Updated: 2024/03/28 18:10:31 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	builtin_niel(int argc, char **argv, t_env *env)
{
	t_command	cmd;

	(void)argc;
	(void)argv;
	(void)env;
	cmd.cmd = (char *[]){"cat", "niel", 0};
	cmd.fd_in = 0;
	cmd.fd_out = 1;
	return (exe_command(&cmd, env));
}
