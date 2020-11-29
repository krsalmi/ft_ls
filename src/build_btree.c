/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_btree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:11:24 by ksalmi            #+#    #+#             */
/*   Updated: 2020/07/09 11:04:48 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree	*open_dir_make_btree(const char *path, t_opts *opts)
{
	struct dirent	*sd;
	DIR				*stream;
	t_btree			*root;
	t_btree			*node;
	char			*temp;

	node = NULL;
	root = node;
	if (!(stream = opendir(path)))
		error_check(1, strerror(errno));
	if (stream)
	{
		while ((sd = readdir(stream)))
		{
			if (!(!opts->a_option && sd->d_name[0] == '.'))
			{
				temp = create_new_path(path, sd->d_name);
				node = btree_create_node(temp, sd->d_name);
				node->path = temp;
				btree_add_left(&root, node);
			}
		}
		closedir(stream);
	}
	return (root);
}

t_btree	*add_sub_dirs(t_btree *tree, t_opts *opts)
{
	if (tree == NULL)
		return (tree);
	else
	{
		if (tree && (S_ISDIR(tree->stats.st_mode)) && \
			ft_strcmp(tree->name, ".") && ft_strcmp(tree->name, ".."))
		{
			ft_printf("\n%s:\n", tree->path);
			tree->right = open_dir_make_btree(tree->path, opts);
			sort_branch(tree->right, opts);
			print_directory(tree->right, opts);
			add_sub_dirs(tree->right, opts);
			add_sub_dirs(tree->left, opts);
		}
		else
			add_sub_dirs(tree->left, opts);
	}
	return (tree);
}

t_btree	*build_btree_sort_print(char *arg, t_opts *opts)
{
	t_btree	*root;
	char	*path;

	path = check_dir_name(arg);
	if (opts->specify_dir_name)
		ft_printf("%s:\n", arg);
	root = open_dir_make_btree(path, opts);
	sort_branch(root, opts);
	print_directory(root, opts);
	if (opts->upper_r_option)
		root = add_sub_dirs(root, opts);
	free(path);
	return (root);
}
