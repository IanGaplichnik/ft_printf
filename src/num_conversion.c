/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 09:38:25 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/31 09:38:28 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	base_selector(t_parse *parse)
{
	if (parse->conv == 'd' || parse->conv == 'i' || parse->conv == 'u')
		parse->base = 10;
	if (parse->conv == 'o')
		parse->base = 8;
	if (parse->conv == 'x' || parse->conv == 'X')
		parse->base = 16;
}

void	arg_conv_receiver(t_parse *parse, intmax_t *num)
{
	if (parse->length == 0 && (parse->conv != 'u' && parse->conv != 'x' && parse->conv != 'X'))
		*num = (int)va_arg(parse->ap, long long);
	if (parse->length == 0 && (parse->conv == 'u' || parse->conv == 'x' || parse->conv == 'X'))
		*num = (unsigned int)va_arg(parse->ap, long long);
	if (parse->length == 1)
		*num = (char)va_arg(parse->ap, long long);
	if (parse->length == 2)
		*num = (short)va_arg(parse->ap, long long);
	if (parse->length == 3 || parse->length == 5)
		*num = (long long)va_arg(parse->ap, long long);
	if (parse->length == 4)
		*num = (long)va_arg(parse->ap, long long);
}

char	*num_to_string(t_parse *parse, intmax_t num)
{
	int cap;

	if (parse->conv == 'X')
		cap = 1;
	else
		cap = 0;
	if (parse->length == 0)
		return (ft_itoa_base((unsigned int)num, parse->base, cap));
	if (parse->length == 1)
		return (ft_itoa_base((unsigned char)num, parse->base, cap));
	if (parse->length == 2)
		return (ft_itoa_base((unsigned short)num, parse->base, cap));
	if (parse->length == 3 || parse->length == 5)
		return (ft_itoa_base((unsigned long long)num, parse->base, cap));
	if (parse->length == 4)
		return (ft_itoa_base((unsigned long)num, parse->base, cap));
	else
		return (NULL);
}

void	print_specifier(t_parse *parse, char *num)
{
	if (parse->conv == 'd' || parse->conv == 'i' || parse->conv == 'o' || parse->conv == 'u' || parse->conv == 'x' || parse->conv == 'X')
		print_di(parse, num);
}

void print_nums(t_parse *parse)
{
	intmax_t num;
	char *res;
	char *tmp;

	base_selector(parse);
	arg_conv_receiver(parse, &num);
	if (num < 0)
	{
		parse->neg = 1;
		num = -num;
	}
	res = num_to_string(parse, num);
	if (!ft_strcmp(res, "-9223372036854775808"))
	{
		tmp = res;
		res = ft_strdup("9223372036854775808");
		free(tmp);
	}
	print_specifier(parse, res);
}
