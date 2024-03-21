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

int	builtin_set(int argc, char **argv, t_env *env)
{
	(void)	argc;
	
	if (!ft_bst_find(&env->envp, argv[1]))
		ft_bst_setvar(&env->vars, argv[1], argv[2]);
	else
		ft_bst_setvar(&env->envp, argv[1], argv[2]);
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
