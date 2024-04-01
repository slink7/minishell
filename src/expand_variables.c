/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:37:27 by scambier          #+#    #+#             */
/*   Updated: 2024/04/01 14:34:43 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "header.h"

static int	strcount(char *str, char c, int len)
{
	int	out;

	out = 0;
	while (--len >= 0)
		out += str[len] == c;
	return (out);
}

static void	add_var(t_strbuilder *builder, char *str, int *at, t_env *env)
{
	char	*temp;
	char	*ve;

	if (strcount(str, '\'', *at) % 2 == 0)
	{
		ve = ft_strchrf(str + *at, w, 1);
		if (!ve)
			ve = str + ft_strlen(str);
		strend(ve);
		temp = env_var_get(env, str + *at);
		if (temp && *temp)
		{
			temp = ft_strdup(temp);
			strnesc(temp, 0);
			ft_strbuilder_addstr(builder, temp, 0);
			free(temp);
		}
		strend(ve);
		*at += ve - str - *at;
	}
	else
		ft_strbuilder_addchar(builder, '$');
}

void	expand_variables(char **str, t_env *env)
{
	t_strbuilder	*builder;
	int				chr;
	int				k;

	builder = ft_strbuilder_new();
	k = 0;
	chr = ft_strchri((*str), '$');
	while (chr > -1)
	{
		if (chr > 0)
			ft_strbuilder_addstr(builder, (*str) + k, chr);
		k += chr + 1;
		add_var(builder, *str, &k, env);
		chr = ft_strchri((*str) + k, '$');
	}
	ft_strbuilder_addstr(builder, (*str) + k, 0);
	free(*str);
	*str = ft_strbuilder_build(builder);
	ft_strbuilder_free(&builder);
}
