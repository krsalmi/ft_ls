/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_long_form_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:59 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:13:01 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_name_symlink(char *n, char *p, struct stat in, t_opts *opts)
{
	char	buf[MAX_BUF_SIZE];
	char	*name;
	char	*path;

	name = n;
	path = p;
	if (opts->g_option)
		print_color(in, name);
	else
		ft_printf("%s", name);
	if (name && is_symlink(path))
	{
		ft_bzero(buf, MAX_BUF_SIZE);
		ft_printf(" -> ");
		if (readlink(path, buf, MAX_BUF_SIZE) == -1)
			error_check(3, strerror(errno));
		ft_printf("%s", buf);
	}
	ft_putchar('\n');
}

static char	print_setuidgid_sticky(mode_t st_mode, mode_t compare, char type)
{
	if (compare == S_ISUID)
	{
		if (type != 'd' && (st_mode & S_ISUID) && (st_mode & S_IXUSR))
			return ('s');
		else if (type != 'd' && !(st_mode & S_IXUSR) && (st_mode & S_ISUID))
			return ('S');
		else
			return ((st_mode & S_IXUSR) ? 'x' : '-');
	}
	else if (compare == S_ISGID)
	{
		if ((st_mode & S_ISGID) && (st_mode & S_IXGRP))
			return ('s');
		else if (!(st_mode & S_IXGRP) && (st_mode & S_ISGID))
			return ('S');
		else
			return ((st_mode & S_IXGRP) ? 'x' : '-');
	}
	else
	{
		if (type == 'd' && (st_mode & S_ISVTX))
			return ('t');
		else
			return ((st_mode & S_IXOTH) ? 'x' : '-');
	}
}

void		print_permissions(mode_t st_mode)
{
	char	type;

	type = check_type(st_mode);
	((st_mode & S_IRUSR) ? ft_putchar('r') : ft_putchar('-'));
	((st_mode & S_IWUSR) ? ft_putchar('w') : ft_putchar('-'));
	ft_putchar(print_setuidgid_sticky(st_mode, S_ISUID, type));
	((st_mode & S_IRGRP) ? ft_putchar('r') : ft_putchar('-'));
	((st_mode & S_IWGRP) ? ft_putchar('w') : ft_putchar('-'));
	ft_putchar(print_setuidgid_sticky(st_mode, S_ISGID, type));
	((st_mode & S_IROTH) ? ft_putchar('r') : ft_putchar('-'));
	((st_mode & S_IWOTH) ? ft_putchar('w') : ft_putchar('-'));
	ft_putchar(print_setuidgid_sticky(st_mode, S_ISVTX, type));
}

void		print_owner_group(struct stat info, t_format *format)
{
	struct group	*gr;
	struct passwd	*pw;

	if (!(pw = getpwuid(info.st_uid)))
		ft_printf("%-*d", format->owner, info.st_uid);
	else
		ft_printf("%-*s", format->owner, pw->pw_name);
	if (!(gr = getgrgid(info.st_gid)))
		ft_printf("%-*d", format->group, info.st_gid);
	else
		ft_printf("%-*s", format->group, gr->gr_name);
}

int			print_xattr_acl(char *path)
{
	int			ret;
	acl_t		acl;

	ret = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (ret > 0)
	{
		ft_putchar('@');
		return (1);
	}
	if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		ft_putchar('+');
		return (1);
	}
	return (0);
}
