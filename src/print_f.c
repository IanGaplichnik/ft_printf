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

static int	ifnan_ifinf(t_parse *parse, long double *full)
{
	if (*full != *full)
	{
		parse->zero = false;
		parse->precision = -1;
		precision_check(parse, "nan");
		return (0);
	}
	if (*full == INFINITY || *full == -INFINITY)
	{
		parse->num = ft_strdup("inf");
		if (*full == -INFINITY)
			parse->neg = 1;
		parse->zero = false;
		parse->precision = -1;
		print_di(parse);
		return (0);
	}
	return (1);
}

static int	f_conversion(t_parse *parse, long *intpart, char **fraction, va_list ap)
{
	long double	full;

	if (parse->length == 5)
		full = (long double)va_arg(ap, long double);
	else
		full = (double)va_arg(ap, double);
	if (!ifnan_ifinf(parse, &full))
		return (0);
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
	else if (parse->precision > 18)
		parse->precision = 18;
	return (1);
}

static void	lengths_prepare_f(t_parse *parse, long *intpart,
		int *num_len, int *str_len)
{
	if (parse->neg || parse->plus)
		parse->space = false;
	*num_len = ft_unumlenbase(*intpart, 10) + parse->precision;
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

static void	number_and_space_f(t_parse *parse, int *i, int *str_len, char *fraction)
{
	ft_strcpy(&parse->cur->data[*i], parse->num);
	*i += ft_strlen(parse->num);
	if (parse->precision != 0 || parse->hash)
		parse->cur->data[(*i)++] = '.';
	if (parse->precision != 0)
	{
		ft_strcpy(&parse->cur->data[*i], fraction);
		*i += ft_strlen(fraction);
	}
	if (*i < parse->width)
	{
		ft_memset(&parse->cur->data[*i], ' ', *str_len - *i);
		*i = *str_len;
	}
	parse->cur->ret = *i;
}

void	print_f(t_parse *parse, va_list ap)
{
	long	intpart;
	char	*fraction;
	int		str_len;
	int		num_len;
	int		i;

	i = 0;
	if (f_conversion(parse, &intpart, &fraction, ap))
	{
		precision_add_f(parse, &fraction, &intpart);
		parse->num = ft_uitoa_base(intpart, 10, 0);
		lengths_prepare_f(parse, &intpart, &num_len, &str_len);
		num_width_f(parse, &num_len, &i, &str_len);
		number_and_space_f(parse, &i, &str_len, fraction);
		free(fraction);
		free(parse->num);
	}
}
