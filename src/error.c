/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:11:55 by ksalmi            #+#    #+#             */
/*   Updated: 2020/07/09 11:01:53 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	error_check(int num, char *msg)
{
	if (!(ft_strcmp(msg, "Permission denied")) || !(ft_strcmp(msg, \
		"Operation not permitted")))
	{
		ft_putstr("ft_ls: ");
		ft_putstr(msg);
		ft_putchar('\n');
	}
	else if (num == -1)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
		exit(1);
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("usage: ft_ls [-Ralrt] [file ...]\n", 2);
		exit(1);
	}
}
