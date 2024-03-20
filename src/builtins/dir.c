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

int	ft_cd(int argc, char **argv, t_env *env)
{
	if (chdir(argv[0]) != 0)
	{
		perror("chdir");
		return (1);
    }
	return (0);
}

int	ft_pwd(int argc, char **argv, t_env *env)
{
	char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
        return (1);
    }
	return (0);
}

