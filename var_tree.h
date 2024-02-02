/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:21:42 by scambier          #+#    #+#             */
/*   Updated: 2024/02/02 15:14:18 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_TREE_H
# define VAR_TREE_H

typedef struct s_var
{
	char	*name;
	char	*value;
}	t_var;

typedef struct s_var_tree
{
	t_var				*var;
	struct s_var_tree	*left;
	struct s_var_tree	*right;
}	t_var_tree;

//tree_alloc.c
/**
 * Creates a new var and sets its name as 'name' and its value to 0.
 * @param name the name of the var
*/
t_var		*new_var(char *name);

/**
 * Frees a var, along with its name and value if it has one.
 * @param var the var you want to free
*/
void		free_var(t_var **var);

/**
 * Creates a new var_tree node and sets 'var' to its var.
 * @param var the var to set
 * @return the new var
*/
t_var_tree	*new_var_tree(t_var	*var);

/**
 * Frees a var_tree, along with all his vars (using free_var()).
 * @param tree the var_tree you want to free
*/
void		free_var_tree(t_var_tree **tree);

/**
 * Looks for the 'name' var in the BST 'tree' and returns it.
 * If 'name' var doesn't exists, it creates it where it should be, duping the 'name' as its name.
 * @param tree the BST to search the var in
 * @param name the name of the looked for var
 * @return the new var
*/
t_var		*var_tree_fetch(t_var_tree **tree, char *name);

/**
 * Looks for 'name' var and returns its value,
 * This uses var_tree_fetch()
 * @param tree the tree to look in
 * @param name the name of the looked for var
 * @return the value of the var, or 0 if it isn't set yet
*/
char		*get_var(t_var_tree *tree, char *name);

/**
 * Sets the var 'name' to 'value', it first frees the value to be replaced if it exists and then dups 'value'.
 * This uses var_tree_fetch()
 * @param tree: the tree to act on
 * @param name: the variable name you look for
 * @param value: the value you want to set de variable to
*/
void		set_var(t_var_tree **tree, char *name, char *value);

/**
 * Prints the tree's vars in ASCII order (left, root, right).
 * @param tree the tree to print
*/
void		print_var_tree(t_var_tree	*tree);

#endif