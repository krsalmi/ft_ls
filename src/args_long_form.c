/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_long_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:09:57 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:10:13 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_l_form_array(char **arr, t_format *f, int lim, t_opts *opts)
{
	struct stat		info;
	int				i;
	char			type;
	int				xattr;

	i = 0;
	while (i < lim)
	{
		info = get_struct_stat(arr[i]);
		type = check_type(info.st_mode);
		ft_putchar(type);
		print_permissions(info.st_mode);
		xattr = print_xattr_acl(arr[i]);
		ft_printf("%* d", (f->hard_links - xattr), info.st_nlink);
		print_owner_group(info, f);
		if (type == 'c' || type == 'b')
			print_device(info, f->maj_min);
		else
			ft_printf("%*lld ", f->size, info.st_size);
		print_time(info.st_mtimespec);
		print_name_symlink(arr[i], arr[i], info, opts);
		i++;
	}
}

static void	save_format_specs_array(char **arr, t_format *format, int limit)
{
	int			tmp;
	struct stat	info;
	int			i;
	char		type;

	i = 0;
	while (i < limit)
	{
		info = get_struct_stat(arr[i]);
		if ((int)info.st_nlink > format->hard_links)
			format->hard_links = (int)info.st_nlink;
		if ((tmp = check_owner_namelen(info.st_uid)) > format->owner)
			format->owner = tmp;
		if ((tmp = check_group_namelen(info.st_gid)) > format->group)
			format->group = tmp;
		if ((type = check_type(info.st_mode)) == 'c' || type == 'b')
			check_device_len(info, format->maj_min);
		if ((int)info.st_size > format->size)
			format->size = (int)info.st_size;
		i++;
	}
	format->hard_links = ft_count_digits(format->hard_links);
	format->size = ft_count_digits(format->size);
	if ((format->maj_min[0] + format->maj_min[1] + 1) > format->size)
		format->size = format->maj_min[0] + format->maj_min[1] + 1;
}

void		handle_long_format_file_array(char **arr, int limit, t_opts *opts)
{
	t_format	format;

	format.hard_links = 0;
	format.owner = 0;
	format.group = 0;
	format.size = 0;
	format.maj_min[0] = 0;
	format.maj_min[1] = 0;
	save_format_specs_array(arr, &format, limit);
	add_buffers(&format);
	print_l_form_array(arr, &format, limit, opts);
}
