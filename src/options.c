/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:33 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:34 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_ls(t_opts *opts)
{
	opts->a_option = 0;
	opts->lower_r_option = 0;
	opts->upper_r_option = 0;
	opts->l_option = 0;
	opts->t_option = 0;
	opts->g_option = 0;
	opts->specify_dir_name = 0;
}

int		read_options(char **argv, int argc, t_opts *opts, int i)
{
	int j;

	while (i < argc && argv[i][0] == '-' && argv[i][1])
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'a')
				opts->a_option = 1;
			else if (argv[i][j] == 'l')
				opts->l_option = 1;
			else if (argv[i][j] == 'R')
				opts->upper_r_option = 1;
			else if (argv[i][j] == 'r')
				opts->lower_r_option = 1;
			else if (argv[i][j] == 't')
				opts->t_option = 1;
			else if (argv[i][j] == 'G')
				opts->g_option = 1;
			else
				error_check(-1, &argv[i][j]);
		}
		i++;
	}
	return (i);
}
