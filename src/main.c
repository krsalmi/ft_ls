/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:28 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:29 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	handle_directories(char **argv, int argc, int div, t_opts *opts)
{
	t_btree	*tree;

	while (div < argc)
	{
		tree = build_btree_sort_print(argv[div], opts);
		if (div < argc - 1)
			ft_printf("\n");
		free_btree(tree, opts);
		div++;
	}
}

int			main(int argc, char **argv)
{
	int		i;
	t_opts	opts;
	t_btree	*tree;
	int		div;

	init_ls(&opts);
	i = read_options(argv, argc, &opts, 1);
	if (i < argc)
	{
		div = sort_args_print_files(argv, argc, i, &opts);
		if (div != i && div < argc)
			ft_printf("\n");
		if (!(div == i && div == argc - 1))
			opts.specify_dir_name = 1;
		handle_directories(argv, argc, div, &opts);
	}
	else
	{
		tree = build_btree_sort_print(".", &opts);
		free_btree(tree, &opts);
	}
	return (0);
}
