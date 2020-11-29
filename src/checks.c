/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:11:37 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:11:41 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	check_type(mode_t st_mode)
{
	char	type;

	if (S_ISREG(st_mode))
		type = '-';
	else if (S_ISBLK(st_mode))
		type = 'b';
	else if (S_ISCHR(st_mode))
		type = 'c';
	else if (S_ISDIR(st_mode))
		type = 'd';
	else if (S_ISLNK(st_mode))
		type = 'l';
	else if (S_ISFIFO(st_mode))
		type = 'p';
	else
		type = 's';
	return (type);
}

int		check_group_namelen(gid_t group_num)
{
	struct group	*gr;
	int				len;

	if (!(gr = getgrgid(group_num)))
		len = ft_count_digits(group_num);
	else
		len = ft_strlen(gr->gr_name);
	return (len);
}

int		check_owner_namelen(uid_t owner_num)
{
	struct passwd	*pw;
	int				len;

	if (!(pw = getpwuid(owner_num)))
		len = ft_count_digits(owner_num);
	else
		len = ft_strlen(pw->pw_name);
	return (len);
}
