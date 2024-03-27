/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:36:33 by scambier          #+#    #+#             */
/*   Updated: 2024/03/27 16:25:26 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

char	*env_get_value(t_env *env, char *name)
{
	t_bst	**var;

	var = ft_bst_find(&env->vars, name);
	if (var != 0)
		return ((*var)->var->value);
	var = ft_bst_find(&env->envp, name);
	if (var != 0)
		return ((*var)->var->value);
	return (0);
}

int	env_append_value(t_env *env, char *cmd)
{
	char	*value;

	value = ft_strchr(cmd, '=') + 1;
	*ft_strchr(cmd, '+') = '\0';
	env_var_append(env, cmd, value);
	return (0);
}

int	env_set_value(t_env *env, char *cmd)
{
	char	*sep;

	sep = ft_strchr(cmd, '=');
	*sep = '\0';
	env_var_set(env, cmd, sep + 1);
	return (0);
}

int	env_change_value(t_env *env, char *cmd)
{
	if (*(ft_strchr(cmd, '=') - 1) == '+')
		return (env_append_value(env, cmd));
	else
		return (env_set_value(env, cmd) == 1);
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
	char	*arg;
	t_bst	**var;

	var = ft_bst_find(&env->envp, variable);
	if (!var)
	{
		if (!ft_bst_find(&env->vars, variable))
			arg = value;
		else
			arg = ft_strjoin((*ft_bst_find(&env->vars, variable))->var->value, value);
		ft_bst_setvar(&env->vars, variable, arg);
	}
	else
	{
		arg = ft_strjoin((*var)->var->value, value);
		ft_printf_fd(1, "%s\n", variable);
		ft_bst_setvar(&env->envp, variable, arg);
	}
	return (0);
}