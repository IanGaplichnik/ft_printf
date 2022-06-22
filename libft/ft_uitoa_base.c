/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:10:57 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/17 14:11:06 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*conv(char *res, unsigned long long num, int base, int len)
{
	len -= 1;
	while (num >= (unsigned long long)base)
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

char	*ft_uitoa_base(unsigned long long num, int base, int cap)
{
	size_t	len;
	char	*res;
	int		i;

	i = -1;
	if (base > 36 || base < 2)
		return (NULL);
	len = ft_unumlenbase(num, base);
	res = ft_strnew(len);
	res = conv(res, num, base, len);
	if (cap)
	{
		while (res[++i])
			res[i] = ft_toupper(res[i]);
	}
	return (res);
}
