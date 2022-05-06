/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:51:40 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/05 14:49:33 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	else
	{
		while (*s)
		{
			if (*s == c)
				tmp = (char *)s;
			s++;
		}
	}
	return (tmp);
}
