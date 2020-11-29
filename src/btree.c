/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:11:13 by ksalmi            #+#    #+#             */
/*   Updated: 2020/07/09 11:09:22 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree			*btree_create_node(char *path, char *d_name)
{
	t_btree		*node;
	struct stat	info;

	if (!(node = (t_btree*)malloc(sizeof(t_btree))))
		error_check(2, strerror(errno));
	if (d_name)
	{
		node->left = NULL;
		node->right = NULL;
		ft_strcpy(node->name, d_name);
		info = get_struct_stat(path);
		node->stats = info;
	}
	return (node);
}

void			btree_add_left(t_btree **begin, t_btree *node)
{
	t_btree		*current;

	if (node)
	{
		if (!(*begin))
			*begin = node;
		else
		{
			current = *begin;
			while (current->left)
				current = current->left;
			current->left = node;
		}
	}
}

static t_btree	*free_recursive_btree(t_btree *tree)
{
	if (tree)
	{
		if (tree->left || tree->right)
		{
			if (tree->right)
			{
				free_recursive_btree(tree->right);
				if (tree->left)
					free_recursive_btree(tree->left);
			}
			else
				free_recursive_btree(tree->left);
		}
		free(tree->path);
		free(tree);
		tree = NULL;
	}
	return (tree);
}

void			free_btree(t_btree *tree, t_opts *opts)
{
	t_btree	*tmp;

	if (opts->upper_r_option)
		free_recursive_btree(tree);
	else
	{
		while (tree)
		{
			tmp = tree->left;
			free(tree->path);
			free(tree);
			tree = tmp;
		}
	}
}
