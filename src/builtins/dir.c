/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:04:04 by ymostows          #+#    #+#             */
/*   Updated: 2024/03/20 19:04:04 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "libft.h"
#include "header.h"

int	builtin_cd(int argc, char **argv, t_env *env)
{
	char	old_cwd[1024];
	char	new_cwd[1024];

	(void) argc;
	(void) env;
	if (getcwd(old_cwd, sizeof(old_cwd)) != NULL)
		ft_bst_setvar(&env->envp, "OLDPWD", old_cwd);
	if (chdir(argv[1]) != 0)
	{
		perror("minishell: chdir");
		return (1);
	}
	if (getcwd(new_cwd, sizeof(new_cwd)) != NULL)
		ft_bst_setvar(&env->envp, "PWD", new_cwd);
	return (0);
}

int	builtin_pwd(int argc, char **argv, t_env *env)
{
	char	cwd[1024];

	(void) argc;
	(void) argv;
	(void) env;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("minishell: getcwd");
		return (1);
	}
	return (0);
}
