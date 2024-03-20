/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:55:06 by scambier          #+#    #+#             */
/*   Updated: 2024/03/20 23:45:13 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

int	builtin_cd(int argc, char **argv, t_env *env);
int	builtin_pwd(int argc, char **argv, t_env *env);
int	builtin_exit(int argc, char **argv, t_env *envp);

typedef	struct s_nf {
	char *name;
	int	(*builtin)(int, char**, t_env*);
}	t_nf;

int	(*fetch_builtin(char *cmd))(int, char**, t_env*)
{
	static t_nf	dict[] = {
		(t_nf) { "cd", builtin_cd },
		(t_nf) { "pwd", builtin_pwd },
		(t_nf) { "exit", builtin_exit },
		(t_nf) {0}
	};
	int			k;

	k = -1;
	while (dict[++k].name)
		if (ft_strncmp(cmd, dict[k].name, ft_strlen(cmd)) == 0)
			return (dict[k].builtin);
	return (0);
}
