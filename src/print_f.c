/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:37:58 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/10 15:37:59 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <limits.h>
#include <math.h>

void	f_conversion(t_parse *parse, long *intpart, char **fraction)
{
	long double	full;

	if (parse->length == 0)
		full = (double)va_arg(parse->ap, double);
	else if (parse->length == 1)
		full = (char)va_arg(parse->ap, double);
	else if (parse->length == 2)
		full = (short)va_arg(parse->ap, double);
	else if (parse->length == 3)
		full = (long long)va_arg(parse->ap, double);
	else if (parse->length == 4)
		full = (double)va_arg(parse->ap, double);
	else if (parse->length == 5)
		full = (long double)va_arg(parse->ap, long double);
	if (full < 0 || (1 / full == -INFINITY))
	{
		full = -full;
		parse->neg = 1;
	}
	*intpart = (long)full;
	*fraction = ft_uitoa_base((unsigned long long)((full - *intpart)
				* pow(10, 19)),
			10, 0); //CHANGE POW
	if (parse->precision == -1)
		parse->precision = 6;
}

void	lengths_prepare_f(t_parse *parse, long *intpart, int *num_len, int *str_len)
{
	if (parse->neg || parse->plus)
		parse->space = false;
	*num_len = ft_numlenbase(*intpart, 10) + parse->precision;
	if ((parse->hash && parse->precision == 0) || parse->precision != 0)
		*num_len += 1;
	*str_len = *num_len;
	if (parse->neg || parse->plus || parse->space)
		*str_len += 1;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len != 0)
		list_alloc(NULL, parse, *str_len);
}

void	num_width_f(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
		{
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
			*i += *str_len - *num_len;
			if (parse->neg || parse->plus || parse->space)
				*i -= 1;
		}
	}
	if (parse->neg || parse->plus || parse->space)
	{
		if (parse->neg)
			parse->cur->data[*i] = '-';
		else if (parse->plus)
			parse->cur->data[*i] = '+';
		else if (parse->space)
			parse->cur->data[*i] = ' ';
	}
	*i = ft_strlen(parse->cur->data);
}

void	print_f(t_parse *parse)
{
	long	intpart;
	char	*fraction;
	int		str_len;
	int		num_len;
	int		i;

	i = 0;
	f_conversion(parse, &intpart, &fraction);
	precision_add_f(parse, &fraction, &intpart);
	parse->num = ft_uitoa_base(intpart, 10, 0);
	lengths_prepare_f(parse, &intpart, &num_len, &str_len);
	num_width_f(parse, &num_len, &i, &str_len);
	ft_strcpy(&parse->cur->data[i], parse->num);
	i += ft_strlen(parse->num);
	if (parse->precision != 0 || parse->hash)
		parse->cur->data[i++] = '.';
	if (parse->precision != 0)
	{
		ft_strcpy(&parse->cur->data[i], fraction);
		i += ft_strlen(fraction);
	}
	if (i < parse->width)
	{
		ft_memset(&parse->cur->data[i], ' ', str_len - i);
		i = str_len;
	}
	parse->cur->ret = i;
	free(parse->num);
}
