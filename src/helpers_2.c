/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:22 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:23 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_format	*add_buffers(t_format *format)
{
	format->hard_links = format->hard_links + 2;
	format->owner = format->owner + 2;
	format->group = format->group + 1;
	format->size = format->size + 1;
	return (format);
}

void		content_swap(t_btree **j, t_btree **i)
{
	struct stat	tmp_stats;
	char		*tmp_path;
	char		tmp_name[MAX_BUF_SIZE];
	t_btree		*a;
	t_btree		*b;

	if (*j && *i)
	{
		a = *j;
		b = *i;
		ft_strcpy(tmp_name, a->name);
		ft_bzero(a->name, ft_strlen(a->name));
		tmp_stats = a->stats;
		tmp_path = a->path;
		ft_strcpy(a->name, b->name);
		ft_bzero(b->name, ft_strlen(b->name));
		a->stats = b->stats;
		a->path = b->path;
		ft_strcpy(b->name, tmp_name);
		b->stats = tmp_stats;
		b->path = tmp_path;
	}
}
