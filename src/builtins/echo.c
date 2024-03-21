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

#include "libft.h"
#include <stdio.h>
#include "env.h"

int	builtin_echo(int argc, char **argv, t_env *env)
{
	(void) argc;
	(void) env;
	int	i;

	i = !ft_strncmp(argv[1], "-n", 3) + 1;
	while (argv[i])
	{
		ft_printf_fd(1,"%s", argv[i]);
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3) != 0)
		ft_printf_fd(1,"\n");
	return (0);
}