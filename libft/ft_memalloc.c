/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 19:33:04 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/18 15:35:28 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = (void *)malloc(size);
	if (!mem || size >= SIZE_MAX)
		return (NULL);
	ft_memset(mem, '\0', size);
	return (mem);
}
