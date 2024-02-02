/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tree_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:27:52 by scambier          #+#    #+#             */
/*   Updated: 2024/02/02 14:53:44 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "var_tree.h"

t_var	*new_var(char *name)
{
	t_var	*out;

	out = malloc(sizeof(t_var));
	out->name = name;
	out->value = 0;
	return (out);
}

t_var_tree	*new_var_tree(t_var	*var)
{
	t_var_tree	*out;

	out = malloc(sizeof(t_var_tree));
	out->var = var;
	out->left = 0;
	out->right = 0;
	return (out);
}

void	free_var(t_var **var)
{
	free((*var)->name);
	if ((*var)->value)
		free((*var)->value);
	free(*var);
	*var = 0;
}

void	free_var_tree(t_var_tree **tree)
{
	if (*tree)
	{
		free_var_tree(&(*tree)->left);
		free_var(&(*tree)->var);
		free_var_tree(&(*tree)->right);
		free(*tree);
		*tree = 0;
	}
}
