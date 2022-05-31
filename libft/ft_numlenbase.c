/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlenbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:35:54 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/16 17:36:00 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlenbase(long num, int base)
{
	size_t	len;

	len = 1;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= base)
	{
		num /= base;
		len++;
	}
	return (len);
}
