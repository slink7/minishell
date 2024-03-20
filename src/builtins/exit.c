/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:32:57 by scambier          #+#    #+#             */
/*   Updated: 2024/03/20 20:40:31 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct s_env t_env;

int	builtin_exit(int argc, char **argv, t_env *envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	return (-1);
}