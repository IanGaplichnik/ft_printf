/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:42:25 by igaplich          #+#    #+#             */
/*   Updated: 2021/11/16 19:06:09 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	int		i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	while (*dst)
		dst++;
	i = 0;
	while (*src && (i < (int)(dstsize - dst_len - 1)))
	{
		*dst = *src;
		dst++;
		src++;
		i++;
	}
	*dst = '\0';
	if (dstsize >= dst_len)
		return (dst_len + src_len);
	return (dstsize + src_len);
}
