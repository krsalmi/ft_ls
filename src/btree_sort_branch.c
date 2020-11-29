/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_sort_branch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:10:57 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:11:00 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	sort_branch_t(t_btree **begin, t_opts *opts)
{
	t_btree	*i;
	t_btree	*j;
	int		check;

	i = *begin;
	while (i)
	{
		check = 0;
		j = i->left;
		while (j)
		{
			if ((!opts->lower_r_option && !(compare_time(i->stats, j->stats)))\
				|| (opts->lower_r_option && compare_time(i->stats, j->stats)))
			{
				check = 1;
				content_swap(&j, &i);
				break ;
			}
			j = j->left;
		}
		if (check == 0)
			i = i->left;
	}
}

static void	sort_branch_ascii(t_btree **begin, t_opts *opts)
{
	t_btree	*i;
	t_btree	*j;
	int		check;

	i = *begin;
	while (i)
	{
		check = 0;
		j = i->left;
		while (j)
		{
			if ((!opts->lower_r_option && ft_strcmp(j->name, i->name) < 0) || \
				(opts->lower_r_option && ft_strcmp(j->name, i->name) > 0))
			{
				check = 1;
				content_swap(&j, &i);
				break ;
			}
			j = j->left;
		}
		if (check == 0)
			i = i->left;
	}
}

void		sort_branch(t_btree *tree, t_opts *opts)
{
	if (opts->t_option)
		sort_branch_t(&tree, opts);
	else
		sort_branch_ascii(&tree, opts);
}
