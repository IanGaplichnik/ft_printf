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

//algorithm if %f is a NaN or inf/-inf
static int	ifnan_ifinf(t_parse *parse, long double *full)
{
	if (*full != *full)
	{
		parse->zero = false;
		parse->precision = -1;
		precision_check(parse, "nan");
		return (0);
	}
	if (*full == 1.0 / 0.0 || *full == -1.0 / 0.0)
	{
		parse->num = ft_strdup("inf");
		if (!parse->num)
			return (-1);
		if (*full == -1.0 / 0.0)
			parse->neg = 1;
		parse->zero = false;
		parse->precision = -1;
		if (print_di(parse, 10) == -1)
			return (-1);
		return (0);
	}
	return (1);
}

/*Setting default precision to 6, if no precision is present
in FORMAT string, else, limiting to the max supported precision 18*/
static void	f_precision_adjust(t_parse *parse)
{
	if (parse->precision == -1)
		parse->precision = 6;
	else if (parse->precision > 18)
		parse->precision = 18;
}

//separating %f fraction and int part, checking if it is a number
static int	f_conversion(t_parse *parse, long *intpart,
		char **fraction, va_list ap)
{
	long double			full;
	int					ret;
	unsigned long long	multiplier;

	multiplier = 10000000000000000000UL;
	if (parse->length == 5)
		full = (long double)va_arg(ap, long double);
	else
		full = (double)va_arg(ap, double);
	ret = ifnan_ifinf(parse, &full);
	if (ret == -1 || ret == 0)
		return (ret);
	if (full < 0 || (1 / full == -1.0 / 0.0))
	{
		full = -full;
		parse->neg = 1;
	}
	*intpart = (long)full;
	*fraction = ft_uitoa_base((unsigned long long)((full - *intpart)
				* multiplier), 10, 0);
	if (!(*fraction))
		return (-1);
	f_precision_adjust(parse);
	return (1);
}

//Beginning of %f printing algorithm
int	print_f(t_parse *parse, va_list ap)
{
	long	intpart;
	char	*fraction;
	int		ret;

	fraction = NULL;
	ret = f_conversion(parse, &intpart, &fraction, ap);
	if (ret == -1)
		return (-1);
	if (ret > 0)
	{
		ret = print_fn(parse, &intpart, &fraction);
		if (ret == -1)
		{
			free(fraction);
			return (-1);
		}
	}
	return (ret);
}
