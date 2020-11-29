/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:13:04 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:13:05 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			compare_time(struct stat info_i, struct stat info_j)
{
	if (info_i.st_mtimespec.tv_sec > info_j.st_mtimespec.tv_sec)
		return (1);
	else if (info_i.st_mtimespec.tv_sec == info_j.st_mtimespec.tv_sec)
	{
		if (info_i.st_mtimespec.tv_nsec > info_j.st_mtimespec.tv_nsec)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	check_6_months(struct timespec st_timespec)
{
	time_t	time_file;
	time_t	six_months;
	time_t	current;
	time_t	calc;

	six_months = (60 * 60 * 24 * 365) / 2;
	time_file = st_timespec.tv_sec;
	if ((current = time(NULL)) == -1)
		error_check(5, "Error fetching current time");
	calc = time_file - current;
	if (calc > six_months || calc < -1 * six_months)
		return (1);
	else
		return (0);
}

void		print_time(struct timespec st_mtimespec)
{
	char	*date;
	char	*begin;
	char	*year;

	if (!(date = ctime(&st_mtimespec.tv_sec)))
		error_check(2, strerror(errno));
	begin = &date[4];
	year = &date[19];
	if (!(check_6_months(st_mtimespec)))
		ft_printf("%.12s", begin);
	else
	{
		ft_printf("%.7s", begin);
		ft_printf("%.5s", year);
	}
	ft_putchar(' ');
}
