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
#include <limits.h>

void print_di(t_parse *parse, char *num)
{
	int str_len;
	int num_len;
	int i;
	char *tmp;

	if (*num == '0' && parse->precision == 0)
	{
		free(num);
		num = ft_strdup("");
		num_len = 0;
	}
	else
		num_len = ft_strlen(num);
	if (parse->precision != -1 && parse->precision > num_len)
	{
		tmp = num;
		num = ft_strnew(parse->precision);
		ft_memset(num, '0', parse->precision - num_len);
		ft_strcpy(&num[parse->precision - num_len], tmp);
		free(tmp);
		num_len = parse->precision;
	}
	if (parse->precision != -1)
		parse->zero = 0;
	if ((parse->neg || parse->plus) && !parse->zero)
		num_len += 1;
	if (!parse->neg && parse->space)
		num_len += 1;
	str_len = num_len;
	if (str_len < parse->width)
		str_len = parse->width;
	if (str_len < parse->precision)
		str_len = parse->precision;
	if (str_len == 0)
		return;
	list_alloc(NULL, parse, str_len);
	i = 0;
	if (parse->space && !parse->neg)
		parse->cur->data[i++] = ' ';
	if (num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[i], '0', str_len - num_len);
		if (!parse->zero)
			ft_memset(&parse->cur->data[i], ' ', str_len - num_len);
		i += str_len - num_len;
		if (parse->neg && parse->zero)
		{
			parse->cur->data[0] = '-';
			parse->neg = 0;
		}
		if (parse->plus && !parse->neg && parse->zero)
			parse->cur->data[0] = '+';
	}
	if (parse->plus && !parse->neg && !parse->zero)
		parse->cur->data[i++] = '+';
	if (parse->neg)
		parse->cur->data[i++] = '-';
		
	ft_strcpy(&parse->cur->data[i], num);
	i += ft_strlen(num);
	if (num_len < parse->width && i < str_len)
	{
		ft_memset(&parse->cur->data[i], ' ', parse->width - i);
		i = parse->width;
	}
	parse->cur->ret = i; 
	free(num);
}