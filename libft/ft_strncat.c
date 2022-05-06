/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:34:35 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/05 14:38:55 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*tmp;

	tmp = s1;
	while (*s1)
		s1++;
	while (*s2 && n)
	{
		*s1 = *s2;
		s1++;
		s2++;
		n--;
	}
	*s1 = '\0';
	return (tmp);
}
