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

void	print_di(t_parse *parse, char *num)
{
	int		str_len;
	int		alloc_len;
	int		num_len;
	int		i;
	char	*tmp;

	num_len = ft_strlen(num);
	if (parse->precision != -1 && parse->precision > num_len)
	{
		tmp = num;
		num = ft_strnew(parse->precision);
		ft_memset(num, '0', parse->precision - num_len);
		ft_strncpy(&num[parse->precision - num_len], tmp, num_len);
		free(tmp);
		num_len = ft_strlen(num);
	}
	if (parse->neg && !parse->zero)
		num_len += 1;
	str_len = num_len;
	if (str_len < parse->width)
		str_len = parse->width;
	if (str_len < parse->precision)
		str_len = parse->precision;
	list_alloc(NULL, parse, str_len);
	i = 0;
	if (num_len < parse->width && !parse->dash && parse->width)
	{
		if (parse->zero)
		{
			ft_memset(&parse->cur->data[i], '0', str_len - num_len);
			i += str_len - num_len;
		}
		if (!parse->zero)
		{
			ft_memset(&parse->cur->data[i], ' ', str_len - num_len);
			i += str_len - num_len;
		}
		if (parse->neg && parse->zero)
			parse->cur->data[0] = '-';
		if (parse->plus && !parse->neg)
			parse->cur->data[0] = '+';
	}
	else if (num_len > parse->width)
	{
		if (parse->plus && !parse->neg)
			parse->cur->data[i++] = '+';
		if (parse->space && !parse->neg)
			parse->cur->data[i++] = ' ';
	}
	if (parse->neg && !ft_strchr(parse->cur->data, '-'))
		parse->cur->data[i++] = '-';
	ft_strncpy(&parse->cur->data[i], num, num_len);
	if (num_len < parse->width)
	{
		i = ft_strlen(parse->cur->data);
		ft_memset(&parse->cur->data[i], ' ', parse->width - i);
	}
	parse->cur->ret = ft_strlen(parse->cur->data);
	free(num);
}