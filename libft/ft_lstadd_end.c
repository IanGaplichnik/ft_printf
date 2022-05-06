/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:55:14 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/20 17:55:23 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (!alst || !new)
		return ;
	temp = *alst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
