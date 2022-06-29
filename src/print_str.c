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

//Setting the string with width for %scp conversions
int	print_wid(t_parse *parse, char *string, int len)
{
	if (list_alloc(NULL, parse, parse->width) == -1)
		return (-1);
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
	return (1);
}

//%s precision handling
int	precision_check(t_parse *parse, char *string)
{
	int	len;

	len = ft_strlen(string);
	if (parse->precision != -1 && parse->precision < len)
		len = parse->precision;
	if (!parse->width || (parse->width && parse->width <= len))
	{
		if (list_alloc(string, parse, len) == -1)
			return (-1);
	}
	else if (parse->width && len < parse->width)
	{
		if (print_wid(parse, string, len) == -1)
			return (-1);
	}
	if (len || parse->width)
		parse->cur->ret = ft_strlen(parse->cur->data);
	return (1);
}

//%s printing algorithm
static int	print_str(t_parse *parse, va_list ap)
{
	char	*string;

	string = va_arg(ap, char *);
	if (!string)
	{
		string = ft_strdup("(null)");
		if (!string)
			return (-1);
	}
	if (precision_check(parse, string) == -1)
		return (-1);
	if (ft_strstr(string, "(null)"))
		free(string);
	return (1);
}

int	print_n(t_parse *parse, va_list ap)
{
	int	value;
	int	*variable;

	value = 0;
	parse->cur = parse->head;
	while (parse->cur)
	{
		value += parse->cur->ret;
		parse->cur = parse->cur->next;
	}
	parse->cur = parse->head;
	while (parse->cur->next)
		parse->cur = parse->cur->next;
	variable = va_arg(ap, void *);
	if (variable == NULL)
		return (-1);
	*variable = value;
	return (1);
}

//Calling appropriate function depending on conversion specifier
int	print_conversion(t_parse *parse, va_list ap)
{
	int	ret;

	ret = -1;
	if (parse->conv == 's')
		ret = print_str(parse, ap);
	else if (parse->conv == 'c')
		ret = print_c(parse, ap);
	else if (parse->conv == '%')
		ret = print_perc(parse);
	else if (parse->conv == 'p')
		ret = print_p(parse, ap);
	else if (parse->conv == 'f')
		ret = print_f(parse, ap);
	else if (parse->conv == 'n')
		ret = print_n(parse, ap);
	else
		ret = print_nums(parse, ap);
	return (ret);
}
