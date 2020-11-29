/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devices.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:11:47 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:11:48 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static dev_t	get_major_device(struct stat info)
{
	dev_t	major;

	major = info.st_rdev >> 24;
	return (major);
}

static dev_t	get_minor_device(struct stat info)
{
	dev_t	minor;

	minor = info.st_rdev & 0xffffff;
	return (minor);
}

int				*check_device_len(struct stat info, int *maj_min)
{
	dev_t	major;
	dev_t	minor;
	int		maj_len;
	int		min_len;

	major = get_major_device(info);
	minor = get_minor_device(info);
	if (maj_min[0] < (maj_len = ft_count_digits(major)))
		maj_min[0] = maj_len;
	if (maj_min[1] < (min_len = ft_count_digits(minor)))
		maj_min[1] = min_len;
	return (maj_min);
}

void			print_device(struct stat info, int maj_min[2])
{
	dev_t	major;
	dev_t	minor;

	major = get_major_device(info);
	minor = get_minor_device(info);
	ft_printf(" %*d,", maj_min[0], major);
	ft_printf("%*d ", maj_min[1], minor);
}
