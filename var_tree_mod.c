/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tree_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 01:53:31 by scambier          #+#    #+#             */
/*   Updated: 2024/02/02 02:17:11 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "var_tree.h"

t_var	*var_tree_fetch(t_var_tree **tree, char *name)
{
	int	cmp;

	if (!*tree)
		*tree = new_var_tree(new_var(ft_strdup(name)));
	cmp = ft_strncmp(name, (*tree)->var->name, ft_strlen(name) + 1);
	if (cmp == 0)
		return ((*tree)->var);
	else if (cmp < 0)
		return (var_tree_fetch(&(*tree)->left, name));
	else
		return (var_tree_fetch(&(*tree)->right, name));
}

char	*get_var(t_var_tree *tree, char *name)
{
	return (var_tree_fetch(&tree, name)->value);
}

void	set_var(t_var_tree **tree, char *name, char *value)
{
	t_var	*var;

	var = var_tree_fetch(tree, name);
	if (var->value)
		free(var->value);
	var->value = ft_strdup(value);
}

void	print_var_tree(t_var_tree	*t)
{
	if (t)
	{
		print_var_tree(t->left);
		ft_printf_fd(1, "\'%s\'=\'%s\'\n", t->var->name, t->var->value);
		print_var_tree(t->right);
	}
}
