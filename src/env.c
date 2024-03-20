/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:40:36 by scambier          #+#    #+#             */
/*   Updated: 2024/03/20 23:44:51 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	init_env(t_env *env, char **envp)
{
	int i;
	
	env->envp = 0;
	env->vars = 0;
	i = 0;
	while (envp[i])
	{
		*ft_strchr(envp[i], '=') = '\0';
		ft_bst_setvar(&env->envp, envp[i], envp[i] + ft_strlen(envp[i]) + 1);
		i++;
	}
	env->last_status = 0;
	return (1);
}

int	deinit_env(t_env *env)
{
	ft_bst_free(&env->envp);
	ft_bst_free(&env->vars);
	return (1);
}