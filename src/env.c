/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:40:36 by scambier          #+#    #+#             */
/*   Updated: 2024/03/27 15:02:23 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>

#include "libft.h"
#include "header.h"

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
	env->exp = 0;
	return (1);
}

char	*get_value(char *name, t_env *env)
{
	t_bst	**var;

	var = ft_bst_find(&env->vars, name);
	if (var != 0)
		return ((*var)->var->value);
	var = ft_bst_find(&env->envp, name);
	if (var != 0)
		return ((*var)->var->value);
	else
		return (0);
}

int	deinit_env(t_env *env)
{
	ft_bst_free(&env->envp);
	ft_bst_free(&env->vars);
	if (env->exp)
		ft_strarrfree(env->exp);
	return (1);
}

void	export_env(t_env *env)
{
	if (env->exp)
		ft_strarrfree(env->exp);
	env->exp = ft_bst_export(env->envp);
}
