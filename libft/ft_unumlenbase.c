/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unumlenbase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:03:38 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/17 14:03:39 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unumlenbase(unsigned long long num, int base)
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
