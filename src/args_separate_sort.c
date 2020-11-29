/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_separate_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:10:24 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:10:31 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	separate_files_and_dirs(char **arr, int limit)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < limit)
	{
		j = i + 1;
		while (j < limit)
		{
			if (is_dir(arr[i]) == 1 && is_dir(arr[j]) == 0)
			{
				ft_strswap(&arr[j], &arr[i]);
				break ;
			}
			j++;
		}
	}
	k = -1;
	while (++k < limit)
	{
		if (is_dir(arr[k]))
			break ;
	}
	return (k);
}

static char	**sort_array_ascii(char **arr, int k, t_opts *opts)
{
	int			i;
	int			j;

	i = 0;
	while (i < k)
	{
		j = i + 1;
		while (j < k)
		{
			if ((!opts->lower_r_option && ft_strcmp(arr[j], arr[i]) < 0) || \
				(opts->lower_r_option && ft_strcmp(arr[j], arr[i]) > 0))
			{
				ft_strswap(&arr[j], &arr[i]);
				i = -1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

static char	**sort_array_t(char **arr, int limit, t_opts *opts)
{
	int			i;
	int			j;
	struct stat	info_i;
	struct stat	info_j;

	i = 0;
	while (i < limit)
	{
		info_i = get_struct_stat(arr[i]);
		j = i + 1;
		while (j < limit)
		{
			info_j = get_struct_stat(arr[j]);
			if ((!opts->lower_r_option && !compare_time(info_i, info_j)) ||\
				(opts->lower_r_option && compare_time(info_i, info_j)))
			{
				ft_strswap(&arr[j], &arr[i]);
				i = -1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

static void	sort_files(char **arr, int limit, t_opts *opts)
{
	if (opts->t_option)
		sort_array_t(arr, limit, opts);
	else
		sort_array_ascii(arr, limit, opts);
}

int			sort_args_print_files(char **argv, int argc, int i, t_opts *opts)
{
	int			k;
	int			div;
	char		**dirs;
	char		**files;

	dirs = NULL;
	files = NULL;
	k = separate_files_and_dirs(&argv[i], argc - i);
	if (k != 0)
		files = &argv[i];
	div = k + i;
	if (div < argc)
		dirs = &argv[div];
	if (files)
	{
		sort_files(files, k, opts);
		if (opts->l_option)
			handle_long_format_file_array(files, k, opts);
		else
			print_files(files, k, opts);
	}
	if (dirs)
		sort_files(dirs, (argc - div), opts);
	return (div);
}
