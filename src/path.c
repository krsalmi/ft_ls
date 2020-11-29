/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 01:12:48 by ksalmi            #+#    #+#             */
/*   Updated: 2020/06/05 01:12:50 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*check_dir_name(char *dir_name)
{
	char *temp;

	if (ft_strstr(dir_name, "./") != dir_name && ft_strstr(dir_name, "../") \
		!= dir_name && ft_strstr(dir_name, "/") != dir_name && \
		ft_strcmp(dir_name, "."))
	{
		if (!(temp = ft_strjoin("./", dir_name)))
			error_check(2, strerror((errno = ENOMEM)));
	}
	else
	{
		if (!(temp = ft_strdup(dir_name)))
			error_check(2, strerror((errno = ENOMEM)));
	}
	return (temp);
}

char	*create_new_path(const char *path_name, char *addition)
{
	char	*new_path;
	char	*temp;
	size_t	len;

	len = ft_strlen(path_name);
	if (path_name[len - 1] != '/')
	{
		if (!(temp = ft_strjoin(path_name, "/")))
			error_check(2, strerror(errno));
	}
	else
	{
		while (path_name[len - 1] == '/')
			len--;
		if (!(temp = ft_strsub(path_name, 0, len + 1)))
			error_check(2, strerror(errno));
	}
	new_path = ft_strjoin(temp, addition);
	free(temp);
	return (new_path);
}
