/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:49:45 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/19 17:49:48 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fresh;

	if (!lst || !f)
		return (NULL);
	fresh = f(lst);
	if (!fresh)
		return (NULL);
	fresh->next = ft_lstmap(lst->next, f);
	if (lst->next == NULL)
		free(lst);
	return (fresh);
}
