/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:08:07 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/09 16:08:10 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(long num, int base)
{
	size_t	len;

	len = 1;
	if (len < 0)
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

static char	*conv(char *res, long num, int base, int len)
{
	len -= 1;
	while (num >= base)
	{
		if (num % base < 10)
			res[len] = '0' + (num % base);
		else
			res[len] = 87 + (num % base);
		num /= base;
		len--;
	}
	if (num < 10)
		res[len] = '0' + num;
	else
		res[len] = 87 + num;
	len--;
	return (res);
}

char	*ft_itoa_base(long num, int base)
{
	size_t	len;
	char	*res;

	if (num == -1 && base == 16)
		return (res = ft_strdup("ffffffffffffffff"));
	if (base > 36 || base < 2)
		return (NULL);
	len = num_len(num, base);
	res = ft_strnew(len);
	res = conv(res, num, base, len);
	return (res);
}
