/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:54 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:55 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_color(struct stat info, char *msg)
{
	char	type;
	int		exec;

	type = check_type(info.st_mode);
	if (type == '-' && ((exec = is_exec(info))) == 0)
	{
		ft_printf("%s", msg);
		return ;
	}
	else if (type == 'd')
		ft_printf("\033[00;34m");
	else if (type == 'l')
		ft_printf("\033[00;35m");
	else if (type == 'p')
		ft_printf("\033[40;33m");
	else if (type == 's')
		ft_printf("\033[01;35m");
	else if (type == 'b')
		ft_printf("\033[40;33;01m");
	else if (type == 'c')
		ft_printf("\033[40;33;01m");
	else if (exec == 1)
		ft_printf("\033[00;31m");
	ft_printf("%s", msg);
	ft_printf("\033[0m");
}

void	print_files(char **arr, int limit, t_opts *opts)
{
	int			i;
	struct stat	info;

	i = 0;
	while (i < limit)
	{
		if (opts->g_option)
		{
			info = get_struct_stat(arr[i]);
			print_color(info, arr[i]);
			ft_putchar('\n');
		}
		else
			ft_printf("%s\n", arr[i]);
		i++;
	}
}

void	print_directory(t_btree *tree, t_opts *opts)
{
	t_btree *current;

	current = tree;
	if (opts->l_option)
		handle_long_format(current, opts);
	else
	{
		while (current)
		{
			if (opts->g_option)
			{
				print_color(current->stats, current->name);
				ft_putchar('\n');
			}
			else
				ft_printf("%s\n", current->name);
			current = current->left;
		}
	}
}
