/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:54:06 by ymostows          #+#    #+#             */
/*   Updated: 2024/03/21 16:54:06 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../env.h"
#include <stdio.h>
#include "bst.h"

int	builtin_env(int argc, char **argv, t_env *env)
{
	(void)	argc;
	(void)	argv;
	int			i;

	export_env(env);
	i = 0;
	while (env->export[i] != 0)
	{
		printf("%s\n", env->export[i]);
		i++;
	}
	return (0);
}

int	builtin_append_value(char *variable, char *value, t_env *env)
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
		printf("%s\n", variable);
		ft_bst_setvar(&env->envp, variable, arg);
	}	
	return (0);
}

int	builtin_set(char *variable, char *value, t_env *env)
{
	if (!ft_bst_find(&env->envp, variable))
		ft_bst_setvar(&env->vars, variable, value);
	else
		ft_bst_setvar(&env->envp, variable, value);
	return (0);
}

int	builtin_unset(int argc, char **argv, t_env *env)
{
	(void)	argc;
	
	if (!ft_bst_find(&env->envp, argv[1]))
		ft_bst_remove(&env->vars, argv[1]);
	else
		ft_bst_remove(&env->envp, argv[1]);
	return (0);
}

int	builtin_export(int argc, char **argv, t_env *env)
{
	if (argc == 1)
		return (builtin_env(argc, argv, env));

	if (ft_bst_find(&env->vars, argv[1]) != 0)
		ft_bst_setvar(&env->envp, argv[1], (*ft_bst_find(&env->vars, argv[1]))->var->value);
	else
		ft_bst_setvar(&env->envp, argv[1], "");
	ft_bst_remove(&env->vars, argv[1]);
	return (0);
}
