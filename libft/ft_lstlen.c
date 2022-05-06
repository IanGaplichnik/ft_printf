/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:53:05 by igaplich          #+#    #+#             */
/*   Updated: 2021/12/20 20:53:09 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstlen(t_list **alst)
{
	t_list	*temp;
	size_t	i;

	if (!alst)
		return (-1);
	i = 0;
	temp = *alst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
