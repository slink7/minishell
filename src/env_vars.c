/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:36:33 by scambier          #+#    #+#             */
/*   Updated: 2024/04/02 15:59:41 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "header.h"

char	*env_var_get(t_env *env, char *name)
{
	t_bst	**var;

	if (ft_strncmp(name, "?", ft_strlen(name)) == 0)
		return (env->last_status);
	var = ft_bst_find(&env->vars, name);
	if (var != 0)
		return ((*var)->var->value);
	var = ft_bst_find(&env->envp, name);
	if (var != 0)
		return ((*var)->var->value);
	return (0);
}

int	env_var_set(t_env *env, char *variable, char *value)
{
	if (!ft_bst_find(&env->envp, variable))
		ft_bst_setvar(&env->vars, variable, value);
	else
		ft_bst_setvar(&env->envp, variable, value);
	return (0);
}

int	env_var_append(t_env *env, char *variable, char *value)
{
	char	*temp;

	temp = env_var_get(env, variable);
	if (!temp)
	{
		env_var_set(env, variable, value);
		return (0);
	}
	temp = ft_strjoin(temp, value);
	env_var_set(env, variable, temp);
	free(temp);
	return (0);
}

int	env_var_change(t_env *env, char *cmd)
{
	char	*value;

	if (!cmd)
		return (1);
	value = ft_strchr(cmd, '=');
	if (cmd == value)
		return (1);
	if (value[-1] == '+')
	{
		value[-1] = 0;
		return (env_var_append(env, cmd, value + 1));
	}
	value[0] = 0;
	return (env_var_set(env, cmd, value + 1));
}
