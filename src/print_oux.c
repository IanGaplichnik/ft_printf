/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_oux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igaplich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:57:37 by igaplich          #+#    #+#             */
/*   Updated: 2022/06/08 17:57:46 by igaplich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <limits.h>

void	num_no_width_oux(t_parse *parse, int *i, int *num_len)
{
	if (parse->hash)
	{
		parse->cur->data[(*i)++] = '0';
		if (parse->conv == 'X')
			parse->cur->data[(*i)++] = 'X';
		else if (parse->conv == 'x')
			parse->cur->data[(*i)++] = 'x';
	}
}

void	num_width_oux(t_parse *parse, int *num_len, int *i, int *str_len)
{
	if (parse->hash && parse->precision != -1)
		*num_len += 2;
	if (*num_len < parse->width && !parse->dash)
	{
		if (parse->zero)
			ft_memset(&parse->cur->data[*i], '0', *str_len - *num_len);
		else if (!parse->zero)
			ft_memset(&parse->cur->data[*i], ' ', *str_len - *num_len);
		if (parse->hash && parse->conv == 'X' && parse->zero)
			ft_memset(&parse->cur->data[1], 'X', 1);
		else if (parse->hash && parse->conv == 'x' && parse->zero)
			ft_memset(&parse->cur->data[1], 'x', 1);
		*i += *str_len - *num_len;
	}
}

void	lengths_prepare_oux(int *num_len, int *str_len, t_parse *parse)
{
	if (parse->precision != -1)
		parse->zero = 0;
	if (!parse->neg && parse->space)
		*num_len += 1;
	*str_len = *num_len;
	if (*str_len < parse->width)
		*str_len = parse->width;
	if (*str_len < parse->precision)
		*str_len = parse->precision;
}

void	precision_add_oux(t_parse *parse, int *num_len)
{
	char	*tmp;
	int		i;

	if (parse->precision > *num_len)
	{
		i = 0;
		tmp = parse->num;
		parse->num = ft_strnew(parse->precision);
		if (parse->precision != -1 && parse->precision > *num_len)
			ft_memset(&parse->num[i], '0', parse->precision - *num_len);
		ft_strcpy(&parse->num[parse->precision - *num_len], tmp);
		free(tmp);
		*num_len = parse->precision;
	}
}

void	print_oux(t_parse *parse)
{
	int		str_len;
	int		num_len;
	int		i;

	if (*parse->num == '0')
		parse->hash = 0;
	if (*parse->num == '0' && parse->precision == 0)
	{
		free(parse->num);
		parse->num = ft_strdup("");
		num_len = 0;
	}
	else
		num_len = ft_strlen(parse->num);
	precision_add_oux(parse, &num_len);
	lengths_prepare_oux(&num_len, &str_len, parse);
	if (str_len == 0)
		return ;
	list_alloc(NULL, parse, str_len);
	i = 0;
	num_width_oux(parse, &num_len, &i, &str_len);
	num_no_width_oux(parse, &i, &num_len);
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