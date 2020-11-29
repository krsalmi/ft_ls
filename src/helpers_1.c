/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:13 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:16 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			is_symlink(char *path)
{
	struct stat info;
	int			ret;

	if ((ret = lstat(path, &info)) == -1)
		error_check(1, strerror(errno));
	return (S_ISLNK(info.st_mode));
}

int			is_dir(char *file)
{
	struct stat	info;

	info = get_struct_stat(file);
	return (S_ISDIR(info.st_mode));
}

int			is_exec(struct stat info)
{
	if ((info.st_mode & S_IXUSR) > 0)
		return (1);
	else
		return (0);
}

struct stat	get_struct_stat(char *path)
{
	struct stat	info;
	int			ret;

	if (is_symlink(path))
	{
		if ((ret = lstat(path, &info)) == -1)
			error_check(1, strerror(errno));
	}
	else
	{
		if ((ret = stat(path, &info)) == -1)
			error_check(1, strerror(errno));
	}
	return (info);
}
