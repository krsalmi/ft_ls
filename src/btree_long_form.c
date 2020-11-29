/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_long_form.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:10:43 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:10:48 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_form_spcs(t_btree *tree, t_format *format, t_opts *opts)
{
	int			tmp;
	char		type;

	while (tree)
	{
		if (!(!opts->a_option && tree->name[0] == '.'))
		{
			if ((int)tree->stats.st_nlink > format->hard_links)
				format->hard_links = (int)tree->stats.st_nlink;
			if ((tmp = check_owner_namelen(tree->stats.st_uid)) > format->owner)
				format->owner = tmp;
			if ((tmp = check_group_namelen(tree->stats.st_gid)) > format->group)
				format->group = tmp;
			if ((type = check_type(tree->stats.st_mode)) == 'c' || type == 'b')
				check_device_len(tree->stats, format->maj_min);
			if ((int)tree->stats.st_size > format->size)
				format->size = (int)tree->stats.st_size;
		}
		tree = tree->left;
	}
	format->hard_links = ft_count_digits(format->hard_links);
	format->size = ft_count_digits(format->size);
	if ((format->maj_min[0] + format->maj_min[1] + 1) > format->size)
		format->size = format->maj_min[0] + format->maj_min[1] + 1;
}

static void	print_total_blocks(t_btree *tree, t_opts *opts)
{
	blksize_t blocks;

	blocks = 0;
	while (tree)
	{
		if ((!(!opts->a_option && tree->name[0] == '.')) && \
			!(S_ISDIR(tree->stats.st_mode)))
		{
			blocks += tree->stats.st_blocks;
		}
		tree = tree->left;
	}
	ft_printf("total %d\n", blocks);
}

static void	print_long_form(t_btree *tree, t_format *f, t_opts *opts)
{
	char	type;
	int		xattr;

	print_total_blocks(tree, opts);
	while (tree)
	{
		if (!(!opts->a_option && tree->name[0] == '.'))
		{
			type = check_type(tree->stats.st_mode);
			ft_putchar(type);
			print_permissions(tree->stats.st_mode);
			xattr = print_xattr_acl(tree->path);
			ft_printf("%*d ", (f->hard_links - xattr), tree->stats.st_nlink);
			print_owner_group(tree->stats, f);
			if (type == 'c' || type == 'b')
				print_device(tree->stats, f->maj_min);
			else
				ft_printf("%*lld ", f->size, tree->stats.st_size);
			print_time(tree->stats.st_mtimespec);
			print_name_symlink(tree->name, tree->path, tree->stats, opts);
		}
		tree = tree->left;
	}
}

void		handle_long_format(t_btree *tree, t_opts *opts)
{
	t_format format;

	format.hard_links = 0;
	format.owner = 0;
	format.group = 0;
	format.size = 0;
	format.maj_min[0] = 0;
	format.maj_min[1] = 0;
	save_form_spcs(tree, &format, opts);
	add_buffers(&format);
	print_long_form(tree, &format, opts);
}
