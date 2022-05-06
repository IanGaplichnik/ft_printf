/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:26:37 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/18 23:30:20 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;

	if (!dst && !src)
		return (NULL);
	tmp = (unsigned char *)dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		n--;
		dst++;
		src++;
	}
	return (tmp);
}
