/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:32:57 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 00:02:51 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	builtin_exit(int argc, char **argv, t_env *envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	return (-1);
}
