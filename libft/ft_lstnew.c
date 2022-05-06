/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:16:31 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/13 23:41:16 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	fresh = (t_list *)malloc(sizeof(t_list));
	if (!fresh)
		return (NULL);
	if (!content || !content_size)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
	}
	else
	{
		fresh->content = (size_t *)malloc(content_size);
		if (!fresh->content)
		{
			free(fresh);
			return (NULL);
		}
		fresh->content = ft_memcpy(fresh->content, content, content_size);
		fresh->content_size = content_size;
	}
	fresh->next = NULL;
	return (fresh);
}
