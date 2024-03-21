/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:40:36 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 01:32:06 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>

#include "libft.h"
#include "env.h"

int	init_env(t_env *env, char **envp)
{
	int		i;
	char	*temp;
	
	env->envp = 0;
	env->vars = 0;
	i = 0;
	while (envp[i])
	{
		temp = ft_strchr(envp[i], '=');
		*temp = 0;
		ft_bst_setvar(&env->envp, envp[i], temp + 1);
		i++;
	}
	env->last_status = 0;
	env->export = 0;
	return (1);
}

int	deinit_env(t_env *env)
{
	ft_bst_free(&env->envp);
	ft_bst_free(&env->vars);
	return (1);
}

void	export_env(t_env *env)
{
	if (env->export)
		free(env->export);
	env->export = ft_bst_export(env->envp);
}