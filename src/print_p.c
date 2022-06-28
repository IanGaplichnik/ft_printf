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

void	print_p(t_parse *parse, va_list ap)
{
	long	p;

	p = (long)va_arg(ap, void *);
	parse->num = ft_itoa_base(p, 16, 0);
	if (p == 0 && parse->precision == 0)
	{
		list_alloc("0x", parse, 2);
		free(parse->num);
	}
	else
		print_ux(parse);
}
