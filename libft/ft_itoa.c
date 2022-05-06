/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:04:39 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/06 14:38:58 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(int num)
{
	size_t	i;

	i = 0;
	if (num < 0)
	{
		i++;
		num = -num;
	}
	while ((num / 10) >= 1)
	{
		i++;
		num = num / 10;
	}
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*fresh;

	if (n == -2147483648)
		return (fresh = ft_strdup("-2147483648"));
	else if (n == 0)
		return (fresh = ft_strdup("0"));
	len = ft_count(n);
	fresh = ft_strnew(len);
	if (!fresh)
		return (NULL);
	if (n < 0)
	{
		fresh[0] = '-';
		n = -n;
	}
	len--;
	while (n)
	{
		fresh[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (fresh);
}
