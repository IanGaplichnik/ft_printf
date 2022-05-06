/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:25:00 by igaplich          #+#    #+#             */
/*   Updated: 2021/11/10 15:11:34 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *str1, const char *str)
{
	while ((*str1 == *str) && *str1 && *str)
	{
		str1++;
		str++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str);
}
