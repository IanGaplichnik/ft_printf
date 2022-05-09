/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <igaplich@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:00:33 by igaplich          #+#    #+#             */
/*   Updated: 2022/03/24 12:56:52 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base(int c, int base)
{
	char	str[17];
	char	str2[17];
	int		i;

	i = 0;
	ft_strcpy(str, "0123456789abcdef");
	ft_strcpy(str2, "0123456789ABCDEF");
	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	nb;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	nb = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (base(str[i], str_base) != -1)
	{
		nb = nb * str_base + base(str[i], str_base);
		i++;
	}
	return (nb * sign);
}
