/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:22:17 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/18 15:56:52 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fresh;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strnew(0));
	else
	{
		fresh = ft_strnew(len);
		if (!fresh)
			return (NULL);
		ft_strncpy(fresh, (s + start), len);
		return (fresh);
	}
}
