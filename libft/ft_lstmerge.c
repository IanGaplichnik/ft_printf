/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:57:26 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/20 22:57:30 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmerge(t_list **dst, t_list **src)
{
	t_list	*temp;

	if (!src || !dst)
		return (NULL);
	temp = *dst;
	while (temp->next)
		temp = temp->next;
	temp->next = *src;
	return (*dst);
}
