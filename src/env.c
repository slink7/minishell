/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:40:36 by scambier          #+#    #+#             */
/*   Updated: 2024/04/02 16:07:15 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"
#include <stdlib.h>

int	env_init(t_env *env, char **envp)
{
	int		i;
	char	*temp;

	env->envp = 0;
	env->vars = 0;
	i = -1;
	while (envp[++i])
	{
		temp = ft_strchr(envp[i], '=');
		*temp = 0;
		ft_bst_setvar(&env->envp, envp[i], temp + 1);
	}
	env->last_status = ft_calloc(1, 1);
	env->exp = 0;
	return (1);
}

int	env_deinit(t_env *env)
{
	ft_bst_free(&env->envp);
	ft_bst_free(&env->vars);
	if (env->last_status != 0)
		free(env->last_status);
	if (env->exp)
		ft_strarrfree(env->exp);
	return (1);
}

void	env_export(t_env *env)
{
	if (env->exp)
		ft_strarrfree(env->exp);
	env->exp = ft_bst_export(env->envp);
}
