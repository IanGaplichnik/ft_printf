/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:22:44 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/11 20:22:46 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_d(t_parse *parse)
{
	void	*num;
	short x;

	if (parse->length == 1)
	{
		num = (signed char *)malloc(sizeof(signed char));
		*(signed char *)num = va_arg(parse->ap, int);
	}
	if (parse->length == 2)
	{
		num = (short *)malloc(sizeof(short));
		*(short *)num = va_arg(parse->ap, int);
	}
	if (parse->length == 3 || parse->length == 5)
	{
		num = (long long *)malloc(sizeof(long long));
		*(long long *)num = va_arg(parse->ap, long long);
	}
	if (parse->length == 4)
	{
		num = (long *)malloc(sizeof(long));
		*(long *)num = va_arg(parse->ap, long);
	}
}