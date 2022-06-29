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

//Selecting base of number for different conversions
static int	base_selector(t_parse *parse, const char c)
{
	if (c == 'o')
		return (8);
	if (c == 'x' || c == 'X')
		return (16);
	if (c == 'b')
	{
		parse->conv = 'd';
		return (2);
	}
	return (10);
}

//Receiving an argument for different number conversions (except %f)
static void	arg_conv_receiver(const char conv, int len,
		va_list ap, intmax_t *num)
{
	if (len == 0 && (conv == 'd' || conv == 'i'))
		*num = (int)va_arg(ap, long long);
	else if (len == 0)
		*num = (unsigned int)va_arg(ap, long long);
	else if (len == 1 && (conv == 'd' || conv == 'i'))
		*num = (char)va_arg(ap, long long);
	else if (len == 1)
		*num = (unsigned char)va_arg(ap, long long);
	else if (len == 2 && (conv == 'd' || conv == 'i'))
		*num = (short)va_arg(ap, long long);
	else if (len == 2)
		*num = (unsigned short)va_arg(ap, long long);
	else if (len == 3 || len == 5)
		*num = (long long)va_arg(ap, long long);
	else if (len == 4 && (conv == 'd' || conv == 'i'))
		*num = (long)va_arg(ap, long long);
	else if (len == 4)
		*num = (unsigned long long)va_arg(ap, unsigned long long);
}

//Converting received argument to a string
static char	*num_to_string(t_parse *parse, intmax_t num, int base)
{
	int	cap;

	if (parse->conv == 'X')
		cap = 1;
	else
		cap = 0;
	if (parse->length == 0)
		return (ft_uitoa_base((unsigned int)num, base, cap));
	if (parse->length == 1)
		return (ft_uitoa_base((unsigned char)num, base, cap));
	if (parse->length == 2)
		return (ft_uitoa_base((unsigned short)num, base, cap));
	if (parse->length == 3 || parse->length == 5)
		return (ft_uitoa_base((unsigned long long)num, base, cap));
	if (parse->length == 4)
		return (ft_uitoa_base((unsigned long long)num, base, cap));
	else
		return (NULL);
}

//Selector function to print %diouxXb
static int	print_specifier(t_parse *parse, int base)
{
	int	ret;

	ret = -1;
	if (parse->conv == 'd' || parse->conv == 'i')
		ret = print_di(parse, base);
	else if (parse->conv == 'u' || parse->conv == 'x' || parse->conv == 'X')
		ret = print_ux(parse);
	else if (parse->conv == 'o')
		ret = print_o(parse);
	return (ret);
}

void	invert_negative(t_parse *parse, intmax_t *num_arg)
{
	if (*num_arg < 0)
	{
		parse->neg = 1;
		if (parse->conv != 'o' && parse->conv != 'u'
			&& parse->conv != 'x' && parse->conv != 'X')
			*num_arg *= -1;
	}
}

//Main algorithm to print numbers
int	print_nums(t_parse *parse, va_list ap)
{
	intmax_t	num_arg;
	char		*tmp;
	int			base;

	base = base_selector(parse, parse->conv);
	arg_conv_receiver(parse->conv, parse->length, ap, &num_arg);
	invert_negative(parse, &num_arg);
	parse->num = num_to_string(parse, num_arg, base);
	if (!parse->num)
		return (-1);
	if (!ft_strcmp(parse->num, "-9223372036854775808"))
	{
		tmp = parse->num;
		parse->num = ft_strdup("9223372036854775808");
		free(tmp);
		if (!parse->num)
			return (-1);
	}
	if (print_specifier(parse, base) == -1)
		return (-1);
	return (1);
}
