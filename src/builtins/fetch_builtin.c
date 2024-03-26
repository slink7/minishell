/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:55:06 by scambier          #+#    #+#             */
/*   Updated: 2024/03/26 22:06:51 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "header.h"

typedef struct s_nf {
	char	*name;
	int		(*builtin)(int, char**, t_env*);
}	t_nf;

int	(*fetch_builtin(char *cmd))(int argc, char **argv, t_env *env)
{
	static t_nf	dict[] = {
		(t_nf){"cd", builtin_cd},
		(t_nf){"pwd", builtin_pwd},
		(t_nf){"exit", builtin_exit},
		(t_nf){"export", builtin_export},
		(t_nf){"unset", builtin_unset},
		(t_nf){"env", builtin_env},
		(t_nf){"echo", builtin_echo},
		(t_nf){"niel", builtin_niel},
		(t_nf){0}
	};
	int			k;

	k = -1;
	while (dict[++k].name)
		if (ft_strncmp(cmd, dict[k].name, ft_strlen(cmd)) == 0)
			return (dict[k].builtin);
	return (0);
}
