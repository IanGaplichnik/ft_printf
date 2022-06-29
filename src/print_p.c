/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:21:25 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/22 18:21:28 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

//%p printing algorithm
int	print_p(t_parse *parse, va_list ap)
{
	long	p;

	p = (long)va_arg(ap, void *);
	parse->num = ft_itoa_base(p, 16, 0);
	if (!parse->num)
		return (-1);
	if (p == 0 && parse->precision == 0)
	{
		if (list_alloc("0x", parse, 2) == -1)
			return (-1);
		free(parse->num);
	}
	else if (print_ux(parse) == -1)
		return (-1);
	return (1);
}
