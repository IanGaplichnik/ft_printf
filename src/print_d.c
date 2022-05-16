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
	uintmax_t	num;
	short x;
	char *res;

	if (parse->length == 1)
		num = (signed char)va_arg(parse->ap, int);
	if (parse->length == 2)
		num = (short *)va_arg(parse->ap, int);
	if (parse->length == 3 || parse->length == 5)
		num = (long long *)va_arg(parse->ap, long long);
	if (parse->length == 4)
		num = (long *)va_arg(parse->ap, long);
	// res = uitoa(num);
}