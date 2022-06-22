/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:51:37 by igaplich          #+#    #+#             */
/*   Updated: 2022/05/04 12:51:38 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_wid(t_parse *parse, char *string, int len)
{
	list_alloc(NULL, parse, parse->width);
	if (!parse->dash)
	{
		if (parse->zero)
			ft_memset(parse->cur->data, '0', parse->width - len);
		else
			ft_memset(parse->cur->data, ' ', parse->width - len);
	}
	ft_strncat(parse->cur->data, string, len);
	if (parse->dash)
		ft_memset(&parse->cur->data[len], ' ', parse->width - len);
}

int	precision_check(t_parse *parse, char *string)
{
	int	len;

	len = ft_strlen(string);
	if (parse->precision != -1 && parse->precision < len)
		len = parse->precision;
	if (!parse->width || (parse->width && parse->width <= len))
		list_alloc(string, parse, len);
	if (parse->width && len < parse->width)
		print_wid(parse, string, len);
	if (len || parse->width)
		parse->cur->ret = ft_strlen(parse->cur->data);
	return (0);
}

void	print_str(t_parse *parse)
{
	char	*string;

	string = va_arg(parse->ap, char *);
	if (!string)
		string = "(null)";
	precision_check(parse, string);
}

int	print_conversion(t_parse *parse)
{
	if (parse->conv == 's')
		print_str(parse);
	else if (parse->conv == 'c')
		print_c(parse);
	else if (parse->conv == '%')
		print_perc(parse);
	else if (parse->conv == 'p')
		print_p(parse);
	else if (parse->conv == 'f')
		print_f(parse);
	else
		print_nums(parse);
	return (0);
}
