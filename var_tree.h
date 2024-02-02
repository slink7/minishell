/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:21:42 by scambier          #+#    #+#             */
/*   Updated: 2024/02/02 02:17:00 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_TREE_H
# define VAR_TREE_H

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;


typedef	struct s_var_tree
{
	t_var				*var;
	struct s_var_tree	*left;
	struct s_var_tree	*right;
}	t_var_tree;

//tree_alloc.c
t_var		*new_var(char *name);
void		free_var(t_var **var);
t_var_tree	*new_var_tree(t_var	*var);
void		free_var_tree(t_var_tree **tree);

//tree_mod.c
t_var		*var_tree_fetch(t_var_tree **tree, char *name);
char		*get_var(t_var_tree *tree, char *name);
void		set_var(t_var_tree **tree, char *name, char *value);
void		print_var_tree(t_var_tree	*t);

#endif