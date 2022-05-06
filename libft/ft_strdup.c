/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:56:31 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/03 20:05:24 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new_str;
	int		len;	

	len = ft_strlen(s);
	new_str = ft_strnew(len);
	if (!new_str)
		return (NULL);
	new_str = ft_strcpy(new_str, s);
	return (new_str);
}
