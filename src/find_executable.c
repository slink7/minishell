/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:37:56 by scambier          #+#    #+#             */
/*   Updated: 2024/03/27 13:37:20 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"

#include <stdio.h>

char	*is_executable(char *path, char *file)
{
	char	*temp;

	temp = ft_strsjoin((char*[]){path, "/", file, 0}, "");
	if (access(temp, 0) == 0)
		return (temp);
	free(temp);
	return (0);
}

char	*find_executable(char **paths, char *file)
{
	char	*out;
	char	wd[1024];

	if (!ft_strncmp(file, "/", 1) && access(file, 0) == 0)
		return (ft_strdup(file));
	if (!ft_strncmp(file, "./", 2))
	{
		getcwd(wd, 1024);
		out = is_executable(wd, file);
		if (out)
			return (out);
	}
	while (*paths)
	{
		out = is_executable(paths[0], file);
		if (out)
			return (out);
		paths++;
	}
	return (0);
}
