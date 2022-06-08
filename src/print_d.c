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

void	num_no_width(t_parse *parse, int *i)
{
	if ((parse->conv == 'X' || parse->conv == 'x') && parse->hash
		&& *(parse->num) != '\0')
	{
		parse->cur->data[(*i)++] = '0';
		if (parse->conv == 'X')
			parse->cur->data[(*i)++] = 'X';
		if (parse->conv == 'x')
			parse->cur->data[(*i)++] = 'x';
	}
	if (parse->plus && !parse->neg && !parse->zero)
		parse->cur->data[(*i)++] = '+';
	else if (parse->neg)
		parse->cur->data[(*i)++] = '-';
}

void	num_width(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
		*i += *str_len - *num_len;
		if ((parse->conv == 'X' || parse->conv == 'x')
			&& parse->hash && *parse->num != '\0')
		{
			parse->cur->data[(*i)++] = '0';
			if (parse->conv == 'X')
				parse->cur->data[(*i)++] = 'X';
			else if (parse->conv == 'x')
				parse->cur->data[(*i)++] = 'x';
		}
		if (parse->neg && parse->zero)
		{
			parse->cur->data[0] = '-';
			parse->neg = 0;
		}
		else if (parse->plus && !parse->neg && parse->zero)
			parse->cur->data[0] = '+';
	}
}

void	lengths_prepare(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1)
		parse->zero = 0;
	if ((parse->neg || parse->plus) && !parse->zero)
		*num_len += 1;
	if (!parse->neg && parse->space)
		*num_len += 1;
	if ((parse->conv == 'X' || parse->conv == 'x') && parse->hash
		&& *(parse->num) != '\0')
		*num_len += 2;
	*str_len = *num_len;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
		*str_len = parse->precision;
}

void	precision_add(t_parse *parse, int *num_len)
{
	char	*tmp;

	
	if (parse->precision != -1 && parse->precision > *num_len)
	{
		tmp = parse->num;
		parse->num = ft_strnew(parse->precision);
		ft_memset(parse->num, '0', parse->precision - *num_len);
		ft_strcpy(&parse->num[parse->precision - *num_len], tmp);
		free(tmp);
		*num_len = parse->precision;
	}
}

void	print_di(t_parse *parse)
{
	int		str_len;
	int		num_len;
	int		i;

	if (*parse->num == '0' && parse->precision == 0)
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	else
		num_len = ft_strlen(parse->num);
	precision_add(parse, &num_len);
	lengths_prepare(&num_len, &str_len, parse);
	if (str_len == 0)
		return ;
	list_alloc(NULL, parse, str_len);
	i = 0;
	if (parse->space && !parse->neg)
		parse->cur->data[i++] = ' ';
	num_width(parse, &num_len, &i, &str_len);
	num_no_width(parse, &i);
	ft_strcpy(&parse->cur->data[i], parse->num);
	i += ft_strlen(parse->num);
	if (num_len < parse->width && i < str_len)
	{
		ft_memset(&parse->cur->data[i], ' ', parse->width - i);
		i = parse->width;
	}
	parse->cur->ret = i;
	free(parse->num);
}
