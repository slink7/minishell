/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:47:33 by ymostows          #+#    #+#             */
/*   Updated: 2024/03/21 19:47:33 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "header.h"

int	builtin_echo(int argc, char **argv, t_env *env)
{
	int	i;
	int	has_flag;

	(void) env;
	has_flag = 0;
	if (argc > 1)
		has_flag = ft_strncmp(argv[1], "-n", 3) == 0;
	i = has_flag;
	while (++i < argc)
	{
		ft_printf_fd(1, "%s", argv[i]);
		if (i < argc - 1)
			ft_printf_fd(1, " ");
	}
	if (!has_flag)
		ft_printf_fd(1, "\n");
	return (0);
}
