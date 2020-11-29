/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:33:09 by ksalmi            #+#    #+#             */
/*   Updated: 2020/03/05 15:42:29 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int	check_colors(char *s, long long int i)
{
	if (!ft_strncmp(&s[i], "{BLUE}", 6))
		ft_putstr(BLUE);
	if (!ft_strncmp(&s[i], "{RED}", 5))
		ft_putstr(RED);
	if (!ft_strncmp(&s[i], "{GREEN}", 7))
		ft_putstr(GREEN);
	if (!ft_strncmp(&s[i], "{YELLOW}", 8))
		ft_putstr(YELLOW);
	if (!ft_strncmp(&s[i], "{MAGENTA}", 9))
		ft_putstr(MAGENTA);
	if (!ft_strncmp(&s[i], "{CYAN}", 6))
		ft_putstr(CYAN);
	if (!ft_strncmp(&s[i], "{EOC}", 5))
		ft_putstr(EOC);
	while (s[i] && s[i] != '}')
		i++;
	i += 1;
	return (i);
}
