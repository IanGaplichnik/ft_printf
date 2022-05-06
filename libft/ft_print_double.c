/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:56:35 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/20 14:56:37 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_double(char **str, size_t len)
{
	size_t	y;

	y = 0;
	while (y < len)
	{
		ft_putstr(str[y]);
		ft_putchar('\n');
		y++;
	}
}
