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

#include "libft.h"

typedef	struct s_env t_env;

int	builtin_cd(int argc, char **argv, t_env *env)
{
	if (chdir(argv[0]) != 0)
	{
		perror("minishell: chdir");
		return (1);
    }
	return (0);
}

int	builtin_pwd(int argc, char **argv, t_env *env)
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("minishell: getcwd");
        return (1);
    }
	return (0);
}
