/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:15:15 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/05 14:56:09 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		if (ft_strncmp(needle, haystack, ft_strlen(needle)) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
