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
	if ((!parse->width || (parse->width && parse->width <= len)) && len)
		list_alloc(string, parse, len);
	if (parse->width && len < parse->width)
		print_wid(parse, string, len);
	if (len || parse->width)
		parse->cur->ret = ft_strlen(parse->cur->data);
	return (0);
}

int	print_c(t_parse *parse)
{
	char	conv;

	conv = (char)va_arg(parse->ap, int);
	if (parse->width && parse->width > 1)
		print_wid(parse, &conv, 1);
	else
		list_alloc(&conv, parse, 1);
	parse->cur->ret = ft_strlen(parse->cur->data);
	if (conv == 0)
	{
		if (parse->width > 1)
			parse->cur->ret = parse->width;
		else
			parse->cur->ret = 1;
	}
	return (0);
}

int	print_perc(t_parse *parse)
{
	char	conv;

	conv = '%';
	if (parse->width && parse->width > 1)
		print_wid(parse, &conv, 1);
	else
		list_alloc(&conv, parse, 1);
	parse->cur->ret = ft_strlen(parse->cur->data);
	return (0);
}

void	print_str(t_parse *parse)
{
	char	*string;
	int		len;

	string = va_arg(parse->ap, char *);
	if (!string)
		string = "(null)";
	precision_check(parse, string);
}

void	print_p(t_parse *parse)
{
	char	*addr;
	char	*tmp;
	long	p;
	int		len;

	p = (long)va_arg(parse->ap, void *);
	addr = ft_itoa_base(p, 16);
	tmp = addr;
	addr = ft_strjoin("0x", addr);
	free(tmp);
	precision_check(parse, addr);
	free(addr);
}

int	print_conversion(t_parse *parse)
{
	// printf("string at print = %s\n", *str);
	if (parse->conv == 's')
		print_str(parse);
	if (parse->conv == 'c')
		print_c(parse);
	if (parse->conv == '%')
		print_perc(parse);
	if (parse->conv == 'p')
		print_p(parse);
	if (parse->conv == 'd' || parse->conv == 'i')
		print_d(parse);
	parse_init(parse);
	return (0);
}
