/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymostows <ymostows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:39:30 by scambier          #+#    #+#             */
/*   Updated: 2024/03/21 19:32:31 by ymostows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "libft.h"

typedef struct s_env
{
	t_bst	*envp;
	t_bst	*vars;
	char	**export;
	int		last_status;
}	t_env;

int		init_env(t_env *env, char **envp);
int		deinit_env(t_env *env);
void	export_env(t_env *env);
char	*get_value(char *name, t_env *env);

#endif